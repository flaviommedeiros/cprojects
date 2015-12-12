switch(*paction){
	case TDLS_SETUP_REQUEST:
		ret=On_TDLS_Setup_Req(adapter, precv_frame);
		break;
	case TDLS_SETUP_RESPONSE:
		ret=On_TDLS_Setup_Rsp(adapter, precv_frame);
		break;
	case TDLS_SETUP_CONFIRM:
		ret=On_TDLS_Setup_Cfm(adapter, precv_frame);
		break;
	case TDLS_TEARDOWN:
		ret=On_TDLS_Teardown(adapter, precv_frame);
		break;
	case TDLS_DISCOVERY_REQUEST:
		ret=On_TDLS_Dis_Req(adapter, precv_frame);
		break;
	case TDLS_PEER_TRAFFIC_INDICATION:
		ret=On_TDLS_Peer_Traffic_Indication(adapter, precv_frame);
		break;
	case TDLS_PEER_TRAFFIC_RESPONSE:
		ret=On_TDLS_Peer_Traffic_Rsp(adapter, precv_frame);
		break;
#ifdef CONFIG_TDLS_CH_SW		
	case TDLS_CHANNEL_SWITCH_REQUEST:
		ret=On_TDLS_Ch_Switch_Req(adapter, precv_frame);
		break;
	case TDLS_CHANNEL_SWITCH_RESPONSE:
		ret=On_TDLS_Ch_Switch_Rsp(adapter, precv_frame);
		break;
#endif		
#ifdef CONFIG_WFD			
	/* First byte of WFA OUI */
	case 0x50:
		if (_rtw_memcmp(WFA_OUI, paction, 3)) {
			/* Probe request frame */
			if (*(paction + 3) == 0x04) {
				/* WFDTDLS: for sigma test, do not setup direct link automatically */
				ptdlsinfo->dev_discovered = _TRUE;
				DBG_871X("recv tunneled probe request frame\n");
				issue_tunneled_probe_rsp(adapter, precv_frame);
			}
			/* Probe response frame */ 
			if (*(paction + 3) == 0x05) {
				/* WFDTDLS: for sigma test, do not setup direct link automatically */
				ptdlsinfo->dev_discovered = _TRUE;
				DBG_871X("recv tunneled probe response frame\n");
			}
		}
		break;
#endif /* CONFIG_WFD */
	default:
		DBG_871X("receive TDLS frame %d but not support\n", *paction);
		ret=_FAIL;
		break;
	}
