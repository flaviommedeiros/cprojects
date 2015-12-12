switch (pIE->ElementID)
		{
			case _VENDOR_SPECIFIC_IE_:
				if (_rtw_memcmp(pIE->data, WMM_PARA_OUI, 6))	//WMM
				{
					WMM_param_handler(padapter, pIE);
				}
#if defined(CONFIG_P2P) && defined(CONFIG_WFD)
				else if ( _rtw_memcmp(pIE->data, WFD_OUI, 4))		//WFD
				{
					DBG_871X( "[%s] Found WFD IE\n", __FUNCTION__ );
					WFD_info_handler( padapter, pIE );
				}
#endif				
				break;

#ifdef CONFIG_WAPI_SUPPORT
			case _WAPI_IE_:
				pWapiIE = pIE;
				break;
#endif

			case _HT_CAPABILITY_IE_:	//HT caps
				HT_caps_handler(padapter, pIE);
				break;

			case _HT_EXTRA_INFO_IE_:	//HT info
				HT_info_handler(padapter, pIE);
				break;

#ifdef CONFIG_80211AC_VHT
			case EID_VHTCapability:
				VHT_caps_handler(padapter, pIE);
				break;

			case EID_VHTOperation:
				VHT_operation_handler(padapter, pIE);
				break;
#endif

			case _ERPINFO_IE_:
				ERP_IE_handler(padapter, pIE);
				break;
#ifdef CONFIG_TDLS
			case _EXT_CAP_IE_:
				if (check_ap_tdls_prohibited(pIE->data, pIE->Length) == _TRUE)
					padapter->tdlsinfo.ap_prohibited = _TRUE;
				if (check_ap_tdls_ch_switching_prohibited(pIE->data, pIE->Length) == _TRUE)
					padapter->tdlsinfo.ch_switch_prohibited = _TRUE;
				break;
#endif /* CONFIG_TDLS */
			default:
				break;
		}
