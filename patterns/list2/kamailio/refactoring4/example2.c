#ifdef WITH_XAVP
if (unlikely(ctx.run_flags&DROP_R_F))
#else
		if (unlikely((ctx.run_flags&DROP_R_F) && (msg_status<200)))
#endif /* TM_ONREPLY_FINAL_DROP_OK */
		{
			if (likely(replies_locked)) {
				replies_locked = 0;
				UNLOCK_REPLIES( t );
			}
			goto done;
		}
