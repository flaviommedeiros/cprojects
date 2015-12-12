switch(ptxmgmt->action_code){
		case TDLS_SETUP_REQUEST:
			rtw_build_tdls_setup_req_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
		case TDLS_SETUP_RESPONSE:
			rtw_build_tdls_setup_rsp_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
		case TDLS_SETUP_CONFIRM:
			rtw_build_tdls_setup_cfm_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
		case TDLS_TEARDOWN:
			rtw_build_tdls_teardown_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
		case TDLS_DISCOVERY_REQUEST:
			rtw_build_tdls_dis_req_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;			
		case TDLS_PEER_TRAFFIC_INDICATION:
			rtw_build_tdls_peer_traffic_indication_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
#ifdef CONFIG_TDLS_CH_SW			
		case TDLS_CHANNEL_SWITCH_REQUEST:
			rtw_build_tdls_ch_switch_req_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
		case TDLS_CHANNEL_SWITCH_RESPONSE:
			rtw_build_tdls_ch_switch_rsp_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
#endif			
		case TDLS_PEER_TRAFFIC_RESPONSE:
			rtw_build_tdls_peer_traffic_rsp_ies(padapter, pxmitframe, pframe, ptxmgmt);
			break;
#ifdef CONFIG_WFD			
		case TUNNELED_PROBE_REQ:
			rtw_build_tunneled_probe_req_ies(padapter, pxmitframe, pframe);
			break;
		case TUNNELED_PROBE_RSP:
			rtw_build_tunneled_probe_rsp_ies(padapter, pxmitframe, pframe);
			break;
#endif //CONFIG_WFD
		default:
			res=_FAIL;
			break;
	}
