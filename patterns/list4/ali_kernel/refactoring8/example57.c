STATIC void after_state_ch(struct drbd_conf *mdev, union drbd_state os,
			   union drbd_state ns, enum chg_state_flags flags)
{
	enum drbd_fencing_p fp;
	enum drbd_req_event what = nothing;
	union drbd_state nsm = (union drbd_state){ .i = -1 };

#if DRBD_DEBUG_STATE_CHANGES
	if (ns.seq) {
		drbd_state_dbg(mdev, ns.seq, ns.func, ns.line, ">>os", os);
		drbd_state_dbg(mdev, ns.seq, ns.func, ns.line, ">>ns", ns);
	}
#endif

	if (os.conn != C_CONNECTED && ns.conn == C_CONNECTED) {
		clear_bit(CRASHED_PRIMARY, &mdev->flags);
		if (mdev->p_uuid)
			mdev->p_uuid[UI_FLAGS] &= ~((u64)2);
	}

	fp = FP_DONT_CARE;
	if (get_ldev(mdev)) {
		fp = mdev->ldev->dc.fencing;
		put_ldev(mdev);
	}

	/* Inform userspace about the change... */
	drbd_bcast_state(mdev, ns);

	if (!(os.role == R_PRIMARY && os.disk < D_UP_TO_DATE && os.pdsk < D_UP_TO_DATE) &&
	    (ns.role == R_PRIMARY && ns.disk < D_UP_TO_DATE && ns.pdsk < D_UP_TO_DATE))
		drbd_khelper(mdev, "pri-on-incon-degr");

	/* Here we have the actions that are performed after a
	   state change. This function might sleep */

	nsm.i = -1;
	if (ns.susp_nod) {
		if (os.conn < C_CONNECTED && ns.conn >= C_CONNECTED)
			what = resend;

		if (os.disk == D_ATTACHING && ns.disk > D_ATTACHING)
			what = restart_frozen_disk_io;

		if (what != nothing)
			nsm.susp_nod = 0;
	}

	if (ns.susp_fen) {
		/* case1: The outdate peer handler is successful: */
		if (os.pdsk > D_OUTDATED  && ns.pdsk <= D_OUTDATED) {
			tl_clear(mdev);
			if (test_bit(NEW_CUR_UUID, &mdev->flags)) {
				drbd_uuid_new_current(mdev);
				clear_bit(NEW_CUR_UUID, &mdev->flags);
			}
			spin_lock_irq(&mdev->req_lock);
			_drbd_set_state(_NS(mdev, susp_fen, 0), CS_VERBOSE, NULL);
			spin_unlock_irq(&mdev->req_lock);
		}
		/* case2: The connection was established again: */
		if (os.conn < C_CONNECTED && ns.conn >= C_CONNECTED) {
			clear_bit(NEW_CUR_UUID, &mdev->flags);
			what = resend;
			nsm.susp_fen = 0;
		}
	}

	if (what != nothing) {
		spin_lock_irq(&mdev->req_lock);
		_tl_restart(mdev, what);
		nsm.i &= mdev->state.i;
		_drbd_set_state(mdev, nsm, CS_VERBOSE, NULL);
		spin_unlock_irq(&mdev->req_lock);
	}

	/* Became sync source.  With protocol >= 96, we still need to send out
	 * the sync uuid now. Need to do that before any drbd_send_state, or
	 * the other side may go "paused sync" before receiving the sync uuids,
	 * which is unexpected. */
	if ((os.conn != C_SYNC_SOURCE && os.conn != C_PAUSED_SYNC_S) &&
	    (ns.conn == C_SYNC_SOURCE || ns.conn == C_PAUSED_SYNC_S) &&
	    mdev->agreed_pro_version >= 96 && get_ldev(mdev)) {
		drbd_gen_and_send_sync_uuid(mdev);
		put_ldev(mdev);
	}

	/* Do not change the order of the if above and the two below... */
	if (os.pdsk == D_DISKLESS && ns.pdsk > D_DISKLESS) {      /* attach on the peer */
		drbd_send_uuids(mdev);
		drbd_send_state(mdev);
	}
	/* No point in queuing send_bitmap if we don't have a connection
	 * anymore, so check also the _current_ state, not only the new state
	 * at the time this work was queued. */
	if (os.conn != C_WF_BITMAP_S && ns.conn == C_WF_BITMAP_S &&
	    mdev->state.conn == C_WF_BITMAP_S)
		drbd_queue_bitmap_io(mdev, &drbd_send_bitmap, NULL,
				"send_bitmap (WFBitMapS)",
				BM_LOCKED_TEST_ALLOWED);

	/* Lost contact to peer's copy of the data */
	if ((os.pdsk >= D_INCONSISTENT &&
	     os.pdsk != D_UNKNOWN &&
	     os.pdsk != D_OUTDATED)
	&&  (ns.pdsk < D_INCONSISTENT ||
	     ns.pdsk == D_UNKNOWN ||
	     ns.pdsk == D_OUTDATED)) {
		if (get_ldev(mdev)) {
			if ((ns.role == R_PRIMARY || ns.peer == R_PRIMARY) &&
			    mdev->ldev->md.uuid[UI_BITMAP] == 0 && ns.disk >= D_UP_TO_DATE) {
				if (is_susp(mdev->state)) {
					set_bit(NEW_CUR_UUID, &mdev->flags);
				} else {
					drbd_uuid_new_current(mdev);
					drbd_send_uuids(mdev);
				}
			}
			put_ldev(mdev);
		}
	}

	if (ns.pdsk < D_INCONSISTENT && get_ldev(mdev)) {
		if (ns.peer == R_PRIMARY && mdev->ldev->md.uuid[UI_BITMAP] == 0) {
			drbd_uuid_new_current(mdev);
			drbd_send_uuids(mdev);
		}

		/* D_DISKLESS Peer becomes secondary */
		if (os.peer == R_PRIMARY && ns.peer == R_SECONDARY)
			/* We may still be Primary ourselves.
			 * No harm done if the bitmap still changes,
			 * redirtied pages will follow later. */
			drbd_bitmap_io_from_worker(mdev, &drbd_bm_write,
				"demote diskless peer", BM_LOCKED_SET_ALLOWED);
		put_ldev(mdev);
	}

	/* Write out all changed bits on demote.
	 * Though, no need to da that just yet
	 * if there is a resync going on still */
	if (os.role == R_PRIMARY && ns.role == R_SECONDARY &&
		mdev->state.conn <= C_CONNECTED && get_ldev(mdev)) {
		/* No changes to the bitmap expected this time, so assert that,
		 * even though no harm was done if it did change. */
		drbd_bitmap_io_from_worker(mdev, &drbd_bm_write,
				"demote", BM_LOCKED_TEST_ALLOWED);
		put_ldev(mdev);
	}

	/* Last part of the attaching process ... */
	if (ns.conn >= C_CONNECTED &&
	    os.disk == D_ATTACHING && ns.disk == D_NEGOTIATING) {
		drbd_send_sizes(mdev, 0, 0);  /* to start sync... */
		drbd_send_uuids(mdev);
		drbd_send_state(mdev);
	}

	/* We want to pause/continue resync, tell peer. */
	if (ns.conn >= C_CONNECTED &&
	     ((os.aftr_isp != ns.aftr_isp) ||
	      (os.user_isp != ns.user_isp)))
		drbd_send_state(mdev);

	/* In case one of the isp bits got set, suspend other devices. */
	if ((!os.aftr_isp && !os.peer_isp && !os.user_isp) &&
	    (ns.aftr_isp || ns.peer_isp || ns.user_isp))
		suspend_other_sg(mdev);

	/* Make sure the peer gets informed about eventual state
	   changes (ISP bits) while we were in WFReportParams. */
	if (os.conn == C_WF_REPORT_PARAMS && ns.conn >= C_CONNECTED)
		drbd_send_state(mdev);

	if (os.conn != C_AHEAD && ns.conn == C_AHEAD)
		drbd_send_state(mdev);

	/* We are in the progress to start a full sync... */
	if ((os.conn != C_STARTING_SYNC_T && ns.conn == C_STARTING_SYNC_T) ||
	    (os.conn != C_STARTING_SYNC_S && ns.conn == C_STARTING_SYNC_S))
		/* no other bitmap changes expected during this phase */
		drbd_queue_bitmap_io(mdev,
			&drbd_bmio_set_n_write, &abw_start_sync,
			"set_n_write from StartingSync", BM_LOCKED_TEST_ALLOWED);

	/* We are invalidating our self... */
	if (os.conn < C_CONNECTED && ns.conn < C_CONNECTED &&
	    os.disk > D_INCONSISTENT && ns.disk == D_INCONSISTENT)
		/* other bitmap operation expected during this phase */
		drbd_queue_bitmap_io(mdev, &drbd_bmio_set_n_write, NULL,
			"set_n_write from invalidate", BM_LOCKED_MASK);

	/* first half of local IO error, failure to attach,
	 * or administrative detach */
	if (os.disk != D_FAILED && ns.disk == D_FAILED) {
		enum drbd_io_error_p eh;
		int was_io_error;
		/* corresponding get_ldev was in __drbd_set_state, to serialize
		 * our cleanup here with the transition to D_DISKLESS,
		 * so it is safe to dreference ldev here. */
		eh = mdev->ldev->dc.on_io_error;
		was_io_error = test_and_clear_bit(WAS_IO_ERROR, &mdev->flags);

		/* current state still has to be D_FAILED,
		 * there is only one way out: to D_DISKLESS,
		 * and that may only happen after our put_ldev below. */
		if (mdev->state.disk != D_FAILED)
			dev_err(DEV,
				"ASSERT FAILED: disk is %s during detach\n",
				drbd_disk_str(mdev->state.disk));

		if (drbd_send_state(mdev))
			dev_warn(DEV, "Notified peer that I am detaching my disk\n");
		else
			dev_err(DEV, "Sending state for detaching disk failed\n");

		drbd_rs_cancel_all(mdev);

		/* In case we want to get something to stable storage still,
		 * this may be the last chance.
		 * Following put_ldev may transition to D_DISKLESS. */
		drbd_md_sync(mdev);
		put_ldev(mdev);

		if (was_io_error && eh == EP_CALL_HELPER)
			drbd_khelper(mdev, "local-io-error");
	}

        /* second half of local IO error, failure to attach,
         * or administrative detach,
         * after local_cnt references have reached zero again */
        if (os.disk != D_DISKLESS && ns.disk == D_DISKLESS) {
                /* We must still be diskless,
                 * re-attach has to be serialized with this! */
                if (mdev->state.disk != D_DISKLESS)
                        dev_err(DEV,
                                "ASSERT FAILED: disk is %s while going diskless\n",
                                drbd_disk_str(mdev->state.disk));

                mdev->rs_total = 0;
                mdev->rs_failed = 0;
                atomic_set(&mdev->rs_pending_cnt, 0);

		if (drbd_send_state(mdev))
			dev_warn(DEV, "Notified peer that I'm now diskless.\n");
		/* corresponding get_ldev in __drbd_set_state
		 * this may finaly trigger drbd_ldev_destroy. */
		put_ldev(mdev);
	}

	/* Disks got bigger while they were detached */
	if (ns.disk > D_NEGOTIATING && ns.pdsk > D_NEGOTIATING &&
	    test_and_clear_bit(RESYNC_AFTER_NEG, &mdev->flags)) {
		if (ns.conn == C_CONNECTED)
			resync_after_online_grow(mdev);
	}

	/* A resync finished or aborted, wake paused devices... */
	if ((os.conn > C_CONNECTED && ns.conn <= C_CONNECTED) ||
	    (os.peer_isp && !ns.peer_isp) ||
	    (os.user_isp && !ns.user_isp))
		resume_next_sg(mdev);

	/* sync target done with resync.  Explicitly notify peer, even though
	 * it should (at least for non-empty resyncs) already know itself. */
	if (os.disk < D_UP_TO_DATE && os.conn >= C_SYNC_SOURCE && ns.conn == C_CONNECTED)
		drbd_send_state(mdev);

	/* This triggers bitmap writeout of potentially still unwritten pages
	 * if the resync finished cleanly, or aborted because of peer disk
	 * failure, or because of connection loss.
	 * For resync aborted because of local disk failure, we cannot do
	 * any bitmap writeout anymore.
	 * No harm done if some bits change during this phase.
	 */
	if (os.conn > C_CONNECTED && ns.conn <= C_CONNECTED && get_ldev(mdev)) {
		drbd_queue_bitmap_io(mdev, &drbd_bm_write, NULL,
			"write from resync_finished", BM_LOCKED_SET_ALLOWED);
		put_ldev(mdev);
	}

	/* free tl_hash if we Got thawed and are C_STANDALONE */
	if (ns.conn == C_STANDALONE && !is_susp(ns) && mdev->tl_hash)
		drbd_free_tl_hash(mdev);

	/* Upon network connection, we need to start the receiver */
	if (os.conn == C_STANDALONE && ns.conn == C_UNCONNECTED)
		drbd_thread_start(&mdev->receiver);

	/* Terminate worker thread if we are unconfigured - it will be
	   restarted as needed... */
	if (ns.disk == D_DISKLESS &&
	    ns.conn == C_STANDALONE &&
	    ns.role == R_SECONDARY) {
		if (os.aftr_isp != ns.aftr_isp)
			resume_next_sg(mdev);
		/* set in __drbd_set_state, unless CONFIG_PENDING was set */
		if (test_bit(DEVICE_DYING, &mdev->flags))
			drbd_thread_stop_nowait(&mdev->worker);
	}

	drbd_md_sync(mdev);
}
