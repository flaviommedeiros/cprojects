switch (pdrvextra_cmd->ec_id) {
	case DYNAMIC_CHK_WK_CID:
		dynamic_chk_wk_hdl(padapter, pdrvextra_cmd->pbuf,
				   pdrvextra_cmd->type_size);
		break;
	case POWER_SAVING_CTRL_WK_CID:
		rtw_ps_processor23a(padapter);
		break;
	case LPS_CTRL_WK_CID:
		lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type_size);
		break;
#ifdef CONFIG_8723AU_AP_MODE
	case CHECK_HIQ_WK_CID:
		rtw_chk_hi_queue_hdl(padapter);
		break;
#endif /* CONFIG_8723AU_AP_MODE */
	case C2H_WK_CID:
		c2h_evt_hdl(padapter,
			    (struct c2h_evt_hdr *)pdrvextra_cmd->pbuf);
		break;

	default:
		break;
	}
