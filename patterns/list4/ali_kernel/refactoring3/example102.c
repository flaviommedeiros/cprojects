switch (action) {
	case ACT_NOTHING:
		break;
	case ACT_TIMEOUT:
		at_state->waiting = 1;
		break;
	case ACT_INIT:
		cs->at_state.pending_commands &= ~PC_INIT;
		cs->cur_at_seq = SEQ_NONE;
		cs->mode = M_UNIMODEM;
		spin_lock_irqsave(&cs->lock, flags);
		if (!cs->cidmode) {
			spin_unlock_irqrestore(&cs->lock, flags);
			gigaset_free_channels(cs);
			cs->mstate = MS_READY;
			break;
		}
		spin_unlock_irqrestore(&cs->lock, flags);
		cs->at_state.pending_commands |= PC_CIDMODE;
		cs->commands_pending = 1;
		gig_dbg(DEBUG_CMD, "Scheduling PC_CIDMODE");
		break;
	case ACT_FAILINIT:
		dev_warn(cs->dev, "Could not initialize the device.\n");
		cs->dle = 0;
		init_failed(cs, M_UNKNOWN);
		cs->cur_at_seq = SEQ_NONE;
		break;
	case ACT_CONFIGMODE:
		init_failed(cs, M_CONFIG);
		cs->cur_at_seq = SEQ_NONE;
		break;
	case ACT_SETDLE1:
		cs->dle = 1;
		/* cs->inbuf[0].inputstate |= INS_command | INS_DLE_command; */
		cs->inbuf[0].inputstate &=
			~(INS_command | INS_DLE_command);
		break;
	case ACT_SETDLE0:
		cs->dle = 0;
		cs->inbuf[0].inputstate =
			(cs->inbuf[0].inputstate & ~INS_DLE_command)
			| INS_command;
		break;
	case ACT_CMODESET:
		if (cs->mstate == MS_INIT || cs->mstate == MS_RECOVER) {
			gigaset_free_channels(cs);
			cs->mstate = MS_READY;
		}
		cs->mode = M_CID;
		cs->cur_at_seq = SEQ_NONE;
		break;
	case ACT_UMODESET:
		cs->mode = M_UNIMODEM;
		cs->cur_at_seq = SEQ_NONE;
		break;
	case ACT_FAILCMODE:
		cs->cur_at_seq = SEQ_NONE;
		if (cs->mstate == MS_INIT || cs->mstate == MS_RECOVER) {
			init_failed(cs, M_UNKNOWN);
			break;
		}
		if (!reinit_and_retry(cs, -1))
			schedule_init(cs, MS_RECOVER);
		break;
	case ACT_FAILUMODE:
		cs->cur_at_seq = SEQ_NONE;
		schedule_init(cs, MS_RECOVER);
		break;
	case ACT_HUPMODEM:
		/* send "+++" (hangup in unimodem mode) */
		if (cs->connected)
			cs->ops->write_cmd(cs, "+++", 3, NULL);
		break;
	case ACT_RING:
		/* get fresh AT state structure for new CID */
		at_state2 = get_free_channel(cs, ev->parameter);
		if (!at_state2) {
			dev_warn(cs->dev,
			"RING ignored: could not allocate channel structure\n");
			break;
		}

		/* initialize AT state structure
		 * note that bcs may be NULL if no B channel is free
		 */
		at_state2->ConState = 700;
		for (i = 0; i < STR_NUM; ++i) {
			kfree(at_state2->str_var[i]);
			at_state2->str_var[i] = NULL;
		}
		at_state2->int_var[VAR_ZCTP] = -1;

		spin_lock_irqsave(&cs->lock, flags);
		at_state2->timer_expires = RING_TIMEOUT;
		at_state2->timer_active = 1;
		spin_unlock_irqrestore(&cs->lock, flags);
		break;
	case ACT_ICALL:
		handle_icall(cs, bcs, p_at_state);
		break;
	case ACT_FAILSDOWN:
		dev_warn(cs->dev, "Could not shut down the device.\n");
		/* fall through */
	case ACT_FAKESDOWN:
	case ACT_SDOWN:
		cs->cur_at_seq = SEQ_NONE;
		finish_shutdown(cs);
		break;
	case ACT_CONNECT:
		if (cs->onechannel) {
			at_state->pending_commands |= PC_DLE1;
			cs->commands_pending = 1;
			break;
		}
		bcs->chstate |= CHS_D_UP;
		gigaset_i4l_channel_cmd(bcs, ISDN_STAT_DCONN);
		cs->ops->init_bchannel(bcs);
		break;
	case ACT_DLE1:
		cs->cur_at_seq = SEQ_NONE;
		bcs = cs->bcs + cs->curchannel;

		bcs->chstate |= CHS_D_UP;
		gigaset_i4l_channel_cmd(bcs, ISDN_STAT_DCONN);
		cs->ops->init_bchannel(bcs);
		break;
	case ACT_FAKEHUP:
		at_state->int_var[VAR_ZSAU] = ZSAU_NULL;
		/* fall through */
	case ACT_DISCONNECT:
		cs->cur_at_seq = SEQ_NONE;
		at_state->cid = -1;
		if (bcs && cs->onechannel && cs->dle) {
			/* Check for other open channels not needed:
			 * DLE only used for M10x with one B channel.
			 */
			at_state->pending_commands |= PC_DLE0;
			cs->commands_pending = 1;
		} else
			disconnect(p_at_state);
		break;
	case ACT_FAKEDLE0:
		at_state->int_var[VAR_ZDLE] = 0;
		cs->dle = 0;
		/* fall through */
	case ACT_DLE0:
		cs->cur_at_seq = SEQ_NONE;
		at_state2 = &cs->bcs[cs->curchannel].at_state;
		disconnect(&at_state2);
		break;
	case ACT_ABORTHUP:
		cs->cur_at_seq = SEQ_NONE;
		dev_warn(cs->dev, "Could not hang up.\n");
		at_state->cid = -1;
		if (bcs && cs->onechannel)
			at_state->pending_commands |= PC_DLE0;
		else
			disconnect(p_at_state);
		schedule_init(cs, MS_RECOVER);
		break;
	case ACT_FAILDLE0:
		cs->cur_at_seq = SEQ_NONE;
		dev_warn(cs->dev, "Could not leave DLE mode.\n");
		at_state2 = &cs->bcs[cs->curchannel].at_state;
		disconnect(&at_state2);
		schedule_init(cs, MS_RECOVER);
		break;
	case ACT_FAILDLE1:
		cs->cur_at_seq = SEQ_NONE;
		dev_warn(cs->dev,
			 "Could not enter DLE mode. Trying to hang up.\n");
		channel = cs->curchannel;
		cs->bcs[channel].at_state.pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		break;

	case ACT_CID: /* got cid; start dialing */
		cs->cur_at_seq = SEQ_NONE;
		channel = cs->curchannel;
		if (ev->parameter > 0 && ev->parameter <= 65535) {
			cs->bcs[channel].at_state.cid = ev->parameter;
			cs->bcs[channel].at_state.pending_commands |=
				PC_DIAL;
			cs->commands_pending = 1;
			break;
		}
		/* fall through */
	case ACT_FAILCID:
		cs->cur_at_seq = SEQ_NONE;
		channel = cs->curchannel;
		if (!reinit_and_retry(cs, channel)) {
			dev_warn(cs->dev,
				 "Could not get a call ID. Cannot dial.\n");
			at_state2 = &cs->bcs[channel].at_state;
			disconnect(&at_state2);
		}
		break;
	case ACT_ABORTCID:
		cs->cur_at_seq = SEQ_NONE;
		at_state2 = &cs->bcs[cs->curchannel].at_state;
		disconnect(&at_state2);
		break;

	case ACT_DIALING:
	case ACT_ACCEPTED:
		cs->cur_at_seq = SEQ_NONE;
		break;

	case ACT_ABORTACCEPT:	/* hangup/error/timeout during ICALL processing */
		disconnect(p_at_state);
		break;

	case ACT_ABORTDIAL:	/* error/timeout during dial preparation */
		cs->cur_at_seq = SEQ_NONE;
		at_state->pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		break;

	case ACT_REMOTEREJECT:	/* DISCONNECT_IND after dialling */
	case ACT_CONNTIMEOUT:	/* timeout waiting for ZSAU=ACTIVE */
	case ACT_REMOTEHUP:	/* DISCONNECT_IND with established connection */
		at_state->pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		break;
	case ACT_GETSTRING: /* warning: RING, ZDLE, ...
			       are not handled properly anymore */
		at_state->getstring = 1;
		break;
	case ACT_SETVER:
		if (!ev->ptr) {
			*p_genresp = 1;
			*p_resp_code = RSP_ERROR;
			break;
		}
		s = ev->ptr;

		if (!strcmp(s, "OK")) {
			*p_genresp = 1;
			*p_resp_code = RSP_ERROR;
			break;
		}

		for (i = 0; i < 4; ++i) {
			val = simple_strtoul(s, (char **) &e, 10);
			if (val > INT_MAX || e == s)
				break;
			if (i == 3) {
				if (*e)
					break;
			} else if (*e != '.')
				break;
			else
				s = e + 1;
			cs->fwver[i] = val;
		}
		if (i != 4) {
			*p_genresp = 1;
			*p_resp_code = RSP_ERROR;
			break;
		}
		/*at_state->getstring = 1;*/
		cs->gotfwver = 0;
		break;
	case ACT_GOTVER:
		if (cs->gotfwver == 0) {
			cs->gotfwver = 1;
			gig_dbg(DEBUG_ANY,
				"firmware version %02d.%03d.%02d.%02d",
				cs->fwver[0], cs->fwver[1],
				cs->fwver[2], cs->fwver[3]);
			break;
		}
		/* fall through */
	case ACT_FAILVER:
		cs->gotfwver = -1;
		dev_err(cs->dev, "could not read firmware version.\n");
		break;
	case ACT_ERROR:
		gig_dbg(DEBUG_ANY, "%s: ERROR response in ConState %d",
			__func__, at_state->ConState);
		cs->cur_at_seq = SEQ_NONE;
		break;
#ifdef CONFIG_GIGASET_DEBUG
	case ACT_TEST:
		{
			static int count = 3; //2; //1;
			*p_genresp = 1;
			*p_resp_code = count ? RSP_ERROR : RSP_OK;
			if (count > 0)
				--count;
		}
		break;
#endif
	case ACT_DEBUG:
		gig_dbg(DEBUG_ANY, "%s: resp_code %d in ConState %d",
			__func__, ev->type, at_state->ConState);
		break;
	case ACT_WARN:
		dev_warn(cs->dev, "%s: resp_code %d in ConState %d!\n",
			 __func__, ev->type, at_state->ConState);
		break;
	case ACT_ZCAU:
		dev_warn(cs->dev, "cause code %04x in connection state %d.\n",
			 ev->parameter, at_state->ConState);
		break;

	/* events from the LL */
	case ACT_DIAL:
		start_dial(at_state, ev->ptr, ev->parameter);
		break;
	case ACT_ACCEPT:
		start_accept(at_state);
		break;
	case ACT_PROTO_L2:
		gig_dbg(DEBUG_CMD, "set protocol to %u",
			(unsigned) ev->parameter);
		at_state->bcs->proto2 = ev->parameter;
		break;
	case ACT_HUP:
		at_state->pending_commands |= PC_HUP;
		cs->commands_pending = 1;
		gig_dbg(DEBUG_CMD, "Scheduling PC_HUP");
		break;

	/* hotplug events */
	case ACT_STOP:
		do_stop(cs);
		break;
	case ACT_START:
		do_start(cs);
		break;

	/* events from the interface */ // FIXME without ACT_xxxx?
	case ACT_IF_LOCK:
		cs->cmd_result = ev->parameter ? do_lock(cs) : do_unlock(cs);
		cs->waiting = 0;
		wake_up(&cs->waitqueue);
		break;
	case ACT_IF_VER:
		if (ev->parameter != 0)
			cs->cmd_result = -EINVAL;
		else if (cs->gotfwver != 1) {
			cs->cmd_result = -ENOENT;
		} else {
			memcpy(ev->arg, cs->fwver, sizeof cs->fwver);
			cs->cmd_result = 0;
		}
		cs->waiting = 0;
		wake_up(&cs->waitqueue);
		break;

	/* events from the proc file system */ // FIXME without ACT_xxxx?
	case ACT_PROC_CIDMODE:
		spin_lock_irqsave(&cs->lock, flags);
		if (ev->parameter != cs->cidmode) {
			cs->cidmode = ev->parameter;
			if (ev->parameter) {
				cs->at_state.pending_commands |= PC_CIDMODE;
				gig_dbg(DEBUG_CMD, "Scheduling PC_CIDMODE");
			} else {
				cs->at_state.pending_commands |= PC_UMMODE;
				gig_dbg(DEBUG_CMD, "Scheduling PC_UMMODE");
			}
			cs->commands_pending = 1;
		}
		spin_unlock_irqrestore(&cs->lock, flags);
		cs->waiting = 0;
		wake_up(&cs->waitqueue);
		break;

	/* events from the hardware drivers */
	case ACT_NOTIFY_BC_DOWN:
		bchannel_down(bcs);
		break;
	case ACT_NOTIFY_BC_UP:
		bchannel_up(bcs);
		break;
	case ACT_SHUTDOWN:
		do_shutdown(cs);
		break;


	default:
		if (action >= ACT_CMD && action < ACT_CMD + AT_NUM) {
			*pp_command = at_state->bcs->commands[action - ACT_CMD];
			if (!*pp_command) {
				*p_genresp = 1;
				*p_resp_code = RSP_NULL;
			}
		} else
			dev_err(cs->dev, "%s: action==%d!\n", __func__, action);
	}
