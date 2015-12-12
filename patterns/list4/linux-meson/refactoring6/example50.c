if (check_fwstate(pmlmepriv,WIFI_STATION_STATE) == _TRUE
#ifdef CONFIG_CONCURRENT_MODE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _FALSE
#endif
	) {
	#ifdef CONFIG_WOWLAN
		if (check_fwstate(pmlmepriv, _FW_LINKED)) {
			pwrpriv->wowlan_mode = _TRUE;
		} else if (pwrpriv->wowlan_pno_enable == _TRUE) {
			pwrpriv->wowlan_mode |= pwrpriv->wowlan_pno_enable;
		}

	#ifdef CONFIG_P2P_WOWLAN
		if(!rtw_p2p_chk_state(&padapter->wdinfo, P2P_STATE_NONE) || P2P_ROLE_DISABLE != padapter->wdinfo.role)
		{
			pwrpriv->wowlan_p2p_mode = _TRUE;
		}
		if(_TRUE == pwrpriv->wowlan_p2p_mode)
			pwrpriv->wowlan_mode |= pwrpriv->wowlan_p2p_mode;
	#endif //CONFIG_P2P_WOWLAN

		if (pwrpriv->wowlan_mode == _TRUE)
			rtw_suspend_wow(padapter);
		else
			rtw_suspend_normal(padapter);
		
	#else //CONFIG_WOWLAN
		rtw_suspend_normal(padapter);
	#endif //CONFIG_WOWLAN
	} else if (check_fwstate(pmlmepriv,WIFI_AP_STATE) == _TRUE
#ifdef CONFIG_CONCURRENT_MODE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _FALSE
#endif
	) {
	#ifdef CONFIG_AP_WOWLAN
		rtw_suspend_ap_wow(padapter);
	#else
		rtw_suspend_normal(padapter);
	#endif //CONFIG_AP_WOWLAN
#ifdef CONFIG_CONCURRENT_MODE
	} else if (check_fwstate(pmlmepriv,WIFI_STATION_STATE) == _TRUE
		&& check_buddy_fwstate(padapter, WIFI_AP_STATE) == _TRUE) {
	#ifdef CONFIG_AP_WOWLAN
		rtw_suspend_ap_wow(padapter);
	#else
		rtw_suspend_normal(padapter);
	#endif //CONFIG_AP_WOWLAN
#endif
	} else {
		rtw_suspend_normal(padapter);
	}
