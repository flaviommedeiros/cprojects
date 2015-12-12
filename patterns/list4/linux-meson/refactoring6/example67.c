if (check_fwstate(pmlmepriv, WIFI_SITE_MONITOR)
		|| check_fwstate(pmlmepriv, WIFI_UNDER_LINKING|WIFI_UNDER_WPS)
		|| check_fwstate(pmlmepriv, WIFI_AP_STATE)
		|| check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE|WIFI_ADHOC_STATE)
		#if defined(CONFIG_P2P) && defined(CONFIG_IOCTL_CFG80211) && defined(CONFIG_P2P_IPS)
		|| pcfg80211_wdinfo->is_ro_ch
		#elif defined(CONFIG_P2P)
		|| !rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE)
		#endif
		|| rtw_is_scan_deny(padapter)
#ifdef CONFIG_TDLS
		// TDLS link is established.
		|| ( padapter->tdlsinfo.link_established == _TRUE )
#endif // CONFIG_TDLS		
	)
		return _FALSE;
