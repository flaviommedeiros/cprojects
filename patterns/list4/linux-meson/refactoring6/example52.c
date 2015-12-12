if (check_fwstate(pmlmepriv,WIFI_STATION_STATE) == _TRUE
#ifdef CONFIG_CONCURRENT_MODE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _FALSE
#endif
	) {
	#ifdef CONFIG_WOWLAN
		if (pwrpriv->wowlan_mode == _TRUE)
			rtw_resume_process_wow(padapter);
		else
			rtw_resume_process_normal(padapter);
	#else
		rtw_resume_process_normal(padapter);
	#endif

	} else if (check_fwstate(pmlmepriv,WIFI_AP_STATE) == _TRUE
#ifdef CONFIG_CONCURRENT_MODE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _FALSE
#endif
	) {
	#ifdef CONFIG_AP_WOWLAN
		rtw_resume_process_ap_wow(padapter);
	#else
		rtw_resume_process_normal(padapter);
	#endif //CONFIG_AP_WOWLAN
#ifdef CONFIG_CONCURRENT_MODE
	} else if (check_fwstate(pmlmepriv,WIFI_STATION_STATE) == _TRUE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _TRUE) {
	#ifdef CONFIG_AP_WOWLAN
		rtw_resume_process_ap_wow(padapter);
	#else
		rtw_resume_process_normal(padapter);
	#endif //CONFIG_AP_WOWLAN
#endif
	} else {
		rtw_resume_process_normal(padapter);
	}
