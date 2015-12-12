switch (pIE->ElementID)
		{
			case _VENDOR_SPECIFIC_IE_://Get WMM IE.
				if ( _rtw_memcmp(pIE->data, WMM_OUI, 4) )
				{
					WMM_param_handler(padapter, pIE);
				}
				break;

			case _HT_CAPABILITY_IE_:	//Get HT Cap IE.
				pmlmeinfo->HT_caps_enable = 1;
				break;

			case _HT_EXTRA_INFO_IE_:	//Get HT Info IE.
#ifdef CONFIG_80211N_HT
				pmlmeinfo->HT_info_enable = 1;

				//spec case only for cisco's ap because cisco's ap issue assoc rsp using mcs rate @40MHz or @20MHz	
				{				
					struct HT_info_element *pht_info = (struct HT_info_element *)(pIE->data);

					if (pnetwork->Configuration.DSConfig > 14) {
						if ((pregpriv->bw_mode >> 4) > CHANNEL_WIDTH_20)
							cbw40_enable = 1;
					} else {
						if ((pregpriv->bw_mode & 0x0f) > CHANNEL_WIDTH_20)
							cbw40_enable = 1;
					}

					if ((cbw40_enable) && (pht_info->infos[0] & BIT(2)))
					{
						//switch to the 40M Hz mode according to the AP
						pmlmeext->cur_bwmode = CHANNEL_WIDTH_40;
						switch (pht_info->infos[0] & 0x3)
						{
							case 1:
								pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_LOWER;
								break;
			
							case 3:
								pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_UPPER;
								break;
				
							default:
								pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
								pmlmeext->cur_bwmode = CHANNEL_WIDTH_20;
								break;
						}

						DBG_871X("set HT ch/bw before connected\n");
					}
				}
#endif //CONFIG_80211N_HT
				break;
#ifdef CONFIG_80211AC_VHT
			case EID_VHTCapability://Get VHT Cap IE.
				pmlmeinfo->VHT_enable = 1;
				break;

			case EID_VHTOperation://Get VHT Operation IE.
				if((GET_VHT_OPERATION_ELE_CHL_WIDTH(pIE->data) >= 1) 
					&& ((pregpriv->bw_mode >> 4) >= CHANNEL_WIDTH_80)) {
					pmlmeext->cur_bwmode = CHANNEL_WIDTH_80;
					DBG_871X("VHT center ch = %d\n", GET_VHT_OPERATION_ELE_CENTER_FREQ1(pIE->data));
					DBG_871X("set VHT ch/bw before connected\n");
				}
				break;
#endif
			default:
				break;
		}
