switch (C2hEvent.CmdID) {
	case C2H_CCX_TX_RPT:
#ifdef CONFIG_FW_C2H_DEBUG
	case C2H_8723B_FW_DEBUG:
#endif // CONFIG_FW_C2H_DEBUG
		process_c2h_event(padapter, &C2hEvent, pdata);
		break;

	default:
		pdata = rtw_zmalloc(length);
		if (pdata == NULL)
			break;
		_rtw_memcpy(pdata, pbuf, length);
		if (rtw_c2h_packet_wk_cmd(padapter, pdata, length) == _FAIL)
			rtw_mfree(pdata, length);
		break;
	}
