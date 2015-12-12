if (check_fwstate(b_pmlmepriv, WIFI_ASOC_STATE|WIFI_SITE_MONITOR)
			|| check_fwstate(b_pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
			|| check_fwstate(b_pmlmepriv, WIFI_AP_STATE)
			|| check_fwstate(b_pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
			#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211) && defined(CONFIG_P2P_IPS)
			|| b_pcfg80211_wdinfo->is_ro_ch
			#elif defined(CONFIG_P2P)
			|| !rtw_p2p_chk_state(b_pwdinfo, P2P_STATE_NONE)
			#endif
			#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211)
			|| rtw_get_passing_time_ms(b_pcfg80211_wdinfo->last_ro_ch_time) < 3000
			#endif
		) {
			goto exit;
		}
