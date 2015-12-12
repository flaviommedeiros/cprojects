switch (pIE->ElementID)
		{
			case _VENDOR_SPECIFIC_IE_:		
				//to update WMM paramter set while receiving beacon
				if (_rtw_memcmp(pIE->data, WMM_PARA_OUI, 6) && pIE->Length == WLAN_WMM_LEN)	//WMM
				{
					(WMM_param_handler(padapter, pIE))? report_wmm_edca_update(padapter): 0;
				}

				break;

			case _HT_EXTRA_INFO_IE_:	//HT info				
				//HT_info_handler(padapter, pIE);
				bwmode_update_check(padapter, pIE);
				break;
#ifdef CONFIG_80211AC_VHT
			case EID_OpModeNotification:
				rtw_process_vht_op_mode_notify(padapter, pIE->data, psta);
				break;
#endif //CONFIG_80211AC_VHT
			case _ERPINFO_IE_:
				ERP_IE_handler(padapter, pIE);
				VCS_update(padapter, psta);
				break;

#ifdef CONFIG_TDLS
			case _EXT_CAP_IE_:
				if( check_ap_tdls_prohibited(pIE->data, pIE->Length) == _TRUE )
					ptdlsinfo->ap_prohibited = _TRUE;
				if (check_ap_tdls_ch_switching_prohibited(pIE->data, pIE->Length) == _TRUE)
					ptdlsinfo->ch_switch_prohibited = _TRUE;
				break;
#endif //CONFIG_TDLS
			default:
				break;
		}
