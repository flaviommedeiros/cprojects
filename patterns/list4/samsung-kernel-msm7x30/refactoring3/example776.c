switch (id) {
	case AUDPREPROC_CMD_CFG_DONE_MSG: {
		struct audpreproc_cmd_cfg_done_msg cfg_done_msg;

		getevent(&cfg_done_msg, AUDPREPROC_CMD_CFG_DONE_MSG_LEN);
		MM_DBG("AUDPREPROC_CMD_CFG_DONE_MSG: stream id %d preproc \
			type %x\n", cfg_done_msg.stream_id, \
			cfg_done_msg.aud_preproc_type);
		if ((cfg_done_msg.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[cfg_done_msg.stream_id])
			audpreproc->func[cfg_done_msg.stream_id](
			audpreproc->private[cfg_done_msg.stream_id], id,
			&cfg_done_msg);
		break;
	}
	case AUDPREPROC_ERROR_MSG: {
		struct audpreproc_err_msg err_msg;

		getevent(&err_msg, AUDPREPROC_ERROR_MSG_LEN);
		MM_DBG("AUDPREPROC_ERROR_MSG: stream id %d err idx %d\n",
		err_msg.stream_id, err_msg.aud_preproc_err_idx);
		if ((err_msg.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[err_msg.stream_id])
			audpreproc->func[err_msg.stream_id](
			audpreproc->private[err_msg.stream_id], id,
			&err_msg);
		break;
	}
	case AUDPREPROC_CMD_ENC_CFG_DONE_MSG: {
		struct audpreproc_cmd_enc_cfg_done_msg enc_cfg_msg;

		getevent(&enc_cfg_msg, AUDPREPROC_CMD_ENC_CFG_DONE_MSG_LEN);
		MM_DBG("AUDPREPROC_CMD_ENC_CFG_DONE_MSG: stream id %d enc type \
			%d\n", enc_cfg_msg.stream_id, enc_cfg_msg.rec_enc_type);
		if ((enc_cfg_msg.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[enc_cfg_msg.stream_id])
			audpreproc->func[enc_cfg_msg.stream_id](
			audpreproc->private[enc_cfg_msg.stream_id], id,
			&enc_cfg_msg);
		for (n = 0; n < MAX_EVENT_CALLBACK_CLIENTS; ++n) {
			if (audpreproc->cb_tbl[n] &&
					audpreproc->cb_tbl[n]->fn) {
				audpreproc->cb_tbl[n]->fn( \
					audpreproc->cb_tbl[n]->private, \
					id, (void *) &enc_cfg_msg);
			}
		}
		break;
	}
	case AUDPREPROC_CMD_ENC_PARAM_CFG_DONE_MSG: {
		struct audpreproc_cmd_enc_param_cfg_done_msg enc_param_msg;

		getevent(&enc_param_msg,
				AUDPREPROC_CMD_ENC_PARAM_CFG_DONE_MSG_LEN);
		MM_DBG("AUDPREPROC_CMD_ENC_PARAM_CFG_DONE_MSG: stream id %d\n",
				 enc_param_msg.stream_id);
		if ((enc_param_msg.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[enc_param_msg.stream_id])
			audpreproc->func[enc_param_msg.stream_id](
			audpreproc->private[enc_param_msg.stream_id], id,
			&enc_param_msg);
		break;
	}
	case AUDPREPROC_AFE_CMD_AUDIO_RECORD_CFG_DONE_MSG: {
		struct audpreproc_afe_cmd_audio_record_cfg_done
						record_cfg_done;
		getevent(&record_cfg_done,
			AUDPREPROC_AFE_CMD_AUDIO_RECORD_CFG_DONE_MSG_LEN);
		MM_DBG("AUDPREPROC_AFE_CMD_AUDIO_RECORD_CFG_DONE_MSG: \
			stream id %d\n", record_cfg_done.stream_id);
		if ((record_cfg_done.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[record_cfg_done.stream_id])
			audpreproc->func[record_cfg_done.stream_id](
			audpreproc->private[record_cfg_done.stream_id], id,
			&record_cfg_done);
		break;
	}
	case AUDPREPROC_CMD_ROUTING_MODE_DONE_MSG: {
		struct audpreproc_cmd_routing_mode_done  routing_mode_done;

		getevent(&routing_mode_done,
			AUDPREPROC_CMD_ROUTING_MODE_DONE_MSG_LEN);
		MM_DBG("AUDPREPROC_CMD_ROUTING_MODE_DONE_MSG: \
			stream id %d\n", routing_mode_done.stream_id);
		if ((routing_mode_done.stream_id < MAX_ENC_COUNT) &&
				audpreproc->func[routing_mode_done.stream_id])
			audpreproc->func[routing_mode_done.stream_id](
			audpreproc->private[routing_mode_done.stream_id], id,
			&routing_mode_done);
		break;
	}
#ifdef CONFIG_DEBUG_FS
	case AUDPREPROC_MSG_FEAT_QUERY_DM_DONE:
	   {
	    uint16_t msg[3];
	    getevent(msg, sizeof(msg));
	    MM_INFO("RTC ACK --> %x %x %x\n", msg[0], msg[1], msg[2]);
	    acdb_rtc_set_err(msg[2]);
	   }
	break;
#endif
	case ADSP_MESSAGE_ID: {
		MM_DBG("Received ADSP event:module audpreproctask\n");
		break;
	}
	default:
		MM_ERR("Unknown Event %d\n", id);
	}
