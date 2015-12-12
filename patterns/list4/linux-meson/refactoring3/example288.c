switch(pdrvextra_cmd->ec_id)
	{
		case DYNAMIC_CHK_WK_CID://only  primary padapter go to this cmd, but execute dynamic_chk_wk_hdl() for two interfaces
#ifdef CONFIG_CONCURRENT_MODE
			if(padapter->pbuddy_adapter)
			{
				dynamic_chk_wk_hdl(padapter->pbuddy_adapter);
			}	
#endif //CONFIG_CONCURRENT_MODE
			dynamic_chk_wk_hdl(padapter);
			break;
		case POWER_SAVING_CTRL_WK_CID:
			power_saving_wk_hdl(padapter);	
			break;
#ifdef CONFIG_LPS
		case LPS_CTRL_WK_CID:
			lps_ctrl_wk_hdl(padapter, (u8)pdrvextra_cmd->type);
			break;
		case DM_IN_LPS_WK_CID:			
			rtw_dm_in_lps_hdl(padapter);	
			break;
		case LPS_CHANGE_DTIM_CID:
			rtw_lps_change_dtim_hdl(padapter, (u8)pdrvextra_cmd->type);
			break;
#endif
#if (RATE_ADAPTIVE_SUPPORT==1)
		case RTP_TIMER_CFG_WK_CID:
			rpt_timer_setting_wk_hdl(padapter, pdrvextra_cmd->type);
			break;
#endif
#ifdef CONFIG_ANTENNA_DIVERSITY
		case ANT_SELECT_WK_CID:
			antenna_select_wk_hdl(padapter, pdrvextra_cmd->type);
			break;
#endif
#ifdef CONFIG_P2P_PS
		case P2P_PS_WK_CID:
			p2p_ps_wk_hdl(padapter, pdrvextra_cmd->type);
			break;
#endif //CONFIG_P2P_PS
#ifdef CONFIG_P2P
		case P2P_PROTO_WK_CID:
			//	Commented by Albert 2011/07/01
			//	I used the type_size as the type command
			p2p_protocol_wk_hdl( padapter, pdrvextra_cmd->type );
			break;
#endif //CONFIG_P2P
#ifdef CONFIG_AP_MODE
		case CHECK_HIQ_WK_CID:
			rtw_chk_hi_queue_hdl(padapter);
			break;
#endif //CONFIG_AP_MODE
#ifdef CONFIG_INTEL_WIDI
		case INTEl_WIDI_WK_CID:
			intel_widi_wk_hdl(padapter, pdrvextra_cmd->type, pdrvextra_cmd->pbuf);
			break;
#endif //CONFIG_INTEL_WIDI
		//add for CONFIG_IEEE80211W, none 11w can use it
		case RESET_SECURITYPRIV:
			reset_securitypriv_hdl(padapter);
			break;
		case FREE_ASSOC_RESOURCES:
			free_assoc_resources_hdl(padapter);
			break;
		case C2H_WK_CID:
#ifdef CONFIG_C2H_PACKET_EN
			rtw_hal_set_hwreg_with_buf(padapter, HW_VAR_C2H_HANDLE, pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
#else		
			c2h_evt_hdl(padapter, pdrvextra_cmd->pbuf, NULL);
#endif
			break;
#ifdef CONFIG_BEAMFORMING
		case BEAMFORMING_WK_CID:
			beamforming_wk_hdl(padapter, pdrvextra_cmd->type, pdrvextra_cmd->pbuf);
			break;
#endif //CONFIG_BEAMFORMING
		case DM_RA_MSK_WK_CID:
			rtw_dm_ra_mask_hdl(padapter, (struct sta_info *)pdrvextra_cmd->pbuf);
			break;
#ifdef CONFIG_BT_COEXIST
		case BTINFO_WK_CID:
			rtw_btinfo_hdl(padapter ,pdrvextra_cmd->pbuf, pdrvextra_cmd->size);
			break;
#endif
		default:
			break;
	}
