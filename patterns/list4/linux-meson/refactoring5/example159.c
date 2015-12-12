#ifdef CONFIG_P2P
if(rtw_p2p_chk_state(pwdinfo, P2P_STATE_SCAN) || 
				rtw_p2p_chk_state(pwdinfo, P2P_STATE_FIND_PHASE_SEARCH)
			)
			{
				issue_probereq_p2p(padapter, NULL);
				issue_probereq_p2p(padapter, NULL);
				issue_probereq_p2p(padapter, NULL);
			}
			else
			#endif //CONFIG_P2P
			{
				int i;
				for(i=0;i<RTW_SSID_SCAN_AMOUNT;i++){
					if(pmlmeext->sitesurvey_res.ssid[i].SsidLength) {
						/* IOT issue, When wifi_spec is not set, send one probe req without WPS IE. */
						if (padapter->registrypriv.wifi_spec)
							issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), NULL);
						else
							issue_probereq_ex(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), NULL, 0, 0, 0, 0);
						issue_probereq(padapter, &(pmlmeext->sitesurvey_res.ssid[i]), NULL);
					}
				}

				if(pmlmeext->sitesurvey_res.scan_mode == SCAN_ACTIVE) {
					/* IOT issue, When wifi_spec is not set, send one probe req without WPS IE. */
					if (padapter->registrypriv.wifi_spec)
						issue_probereq(padapter, NULL, NULL);
					else
						issue_probereq_ex(padapter, NULL, NULL, 0, 0, 0, 0);
					issue_probereq(padapter, NULL, NULL);
				}
			}
