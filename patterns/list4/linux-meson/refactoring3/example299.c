switch (pIE->ElementID)
		{
			case _VENDOR_SPECIFIC_IE_:
				if ((_rtw_memcmp(pIE->data, RTW_WPA_OUI, 4)) ||
						(_rtw_memcmp(pIE->data, WMM_OUI, 4)) ||
						(_rtw_memcmp(pIE->data, WPS_OUI, 4)))
				{	
					vs_ie_length = pIE->Length;
					if((!padapter->registrypriv.wifi_spec) && (_rtw_memcmp(pIE->data, WPS_OUI, 4)))
					{
						//Commented by Kurt 20110629
						//In some older APs, WPS handshake
						//would be fail if we append vender extensions informations to AP

						vs_ie_length = 14;
					}
					
					pframe = rtw_set_ie(pframe, _VENDOR_SPECIFIC_IE_, vs_ie_length, pIE->data, &(pattrib->pktlen));
				}
				break;

			case EID_WPA2:
				pframe = rtw_set_ie(pframe, EID_WPA2, pIE->Length, pIE->data, &(pattrib->pktlen));
				break;
#ifdef CONFIG_80211N_HT
			case EID_HTCapability:
				if(padapter->mlmepriv.htpriv.ht_option==_TRUE) {
					if (!(is_ap_in_tkip(padapter)))
					{
						_rtw_memcpy(&(pmlmeinfo->HT_caps), pIE->data, sizeof(struct HT_caps_element));

						pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info = cpu_to_le16(pmlmeinfo->HT_caps.u.HT_cap_element.HT_caps_info);

						pframe = rtw_set_ie(pframe, EID_HTCapability, pIE->Length , (u8 *)(&(pmlmeinfo->HT_caps)), &(pattrib->pktlen));
					}
				}
				break;

			case EID_EXTCapability:
				if(padapter->mlmepriv.htpriv.ht_option==_TRUE) {
					pframe = rtw_set_ie(pframe, EID_EXTCapability, pIE->Length, pIE->data, &(pattrib->pktlen));
				}
				break;
#endif //CONFIG_80211N_HT
#ifdef CONFIG_80211AC_VHT
			case EID_VHTCapability:
				if (padapter->mlmepriv.vhtpriv.vht_option ==_TRUE) {
					pframe = rtw_set_ie(pframe, EID_VHTCapability, pIE->Length, pIE->data, &(pattrib->pktlen));
				}
				break;

			case EID_OpModeNotification:
				if (padapter->mlmepriv.vhtpriv.vht_option ==_TRUE) {
					pframe = rtw_set_ie(pframe, EID_OpModeNotification, pIE->Length, pIE->data, &(pattrib->pktlen));
				}
				break;
#endif // CONFIG_80211AC_VHT
			default:
				break;
		}
