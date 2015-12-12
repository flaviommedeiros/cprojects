switch (id) {
	case AUDPP_MSG_STATUS_MSG:{
			unsigned cid = msg[0];
			MM_DBG("status %d %d %d\n", cid, msg[1], msg[2]);

			if ((cid < 5) && audpp->func[cid])
				audpp->func[cid] (audpp->private[cid], id, msg);
			break;
		}
	case AUDPP_MSG_HOST_PCM_INTF_MSG:
		if (audpp->func[5])
			audpp->func[5] (audpp->private[5], id, msg);
		break;
	case AUDPP_MSG_PCMDMAMISSED:
		audpp_handle_pcmdmamiss(audpp, msg[0]);
		break;
	case AUDPP_MSG_CFG_MSG:
		if (msg[0] == AUDPP_MSG_ENA_ENA) {
			MM_INFO("ENABLE\n");
			audpp->enabled = 1;
			audpp_broadcast(audpp, id, msg);
		} else if (msg[0] == AUDPP_MSG_ENA_DIS) {
			MM_INFO("DISABLE\n");
			audpp->enabled = 0;
			wake_up(&audpp->event_wait);
			audpp_broadcast(audpp, id, msg);
		} else {
			MM_ERR("invalid config msg %d\n", msg[0]);
		}
		break;
	case AUDPP_MSG_ROUTING_ACK:
		audpp_notify_clnt(audpp, msg[0], id, msg);
		break;
	case AUDPP_MSG_FLUSH_ACK:
		audpp_notify_clnt(audpp, msg[0], id, msg);
		break;
	case ADSP_MESSAGE_ID:
		MM_DBG("Received ADSP event: module enable/disable \
				(audpptask)");
		break;
	case AUDPP_MSG_AVSYNC_MSG:
		audpp_notify_clnt(audpp, msg[0], id, msg);
		break;
#ifdef CONFIG_DEBUG_FS
	case AUDPP_MSG_FEAT_QUERY_DM_DONE:
		MM_INFO(" RTC ACK --> %x %x %x %x %x %x %x %x\n", msg[0],\
			msg[1], msg[2], msg[3], msg[4], \
			msg[5], msg[6], msg[7]);
		acdb_rtc_set_err(msg[3]);
		break;
#endif
	default:
		MM_INFO("unhandled msg id %x\n", id);
	}
