#ifdef CONFIG_AP_MODE
if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
	{		
		_irqL irqL;
		struct sta_info *psta;
		struct sta_priv *pstapriv = &padapter->stapriv;
		
		//_enter_critical_bh(&(pstapriv->sta_hash_lock), &irqL);		
		//rtw_free_stainfo(padapter, psta);
		//_exit_critical_bh(&(pstapriv->sta_hash_lock), &irqL);		

		DBG_871X_LEVEL(_drv_always_, FUNC_ADPT_FMT" reason=%u, ta=%pM\n"
			, FUNC_ADPT_ARG(padapter), reason, GetAddr2Ptr(pframe));

		psta = rtw_get_stainfo(pstapriv, GetAddr2Ptr(pframe));	
		if(psta)
		{
			u8 updated = _FALSE;
		
			_enter_critical_bh(&pstapriv->asoc_list_lock, &irqL);
			if(rtw_is_list_empty(&psta->asoc_list)==_FALSE)
			{			
				rtw_list_delete(&psta->asoc_list);
				pstapriv->asoc_list_cnt--;
				updated = ap_free_sta(padapter, psta, _FALSE, reason);

			}
			_exit_critical_bh(&pstapriv->asoc_list_lock, &irqL);

			associated_clients_update(padapter, updated);
		}
		

		return _SUCCESS;
	}
	else
#endif
	{
		int	ignore_received_deauth = 0;

		//	Commented by Albert 20130604
		//	Before sending the auth frame to start the STA/GC mode connection with AP/GO, 
		//	we will send the deauth first.
		//	However, the Win8.1 with BRCM Wi-Fi will send the deauth with reason code 6 to us after receieving our deauth.
		//	Added the following code to avoid this case.
		if ( ( pmlmeinfo->state & WIFI_FW_AUTH_STATE ) ||
			( pmlmeinfo->state & WIFI_FW_ASSOC_STATE ) )
		{
			if ( reason == WLAN_REASON_CLASS2_FRAME_FROM_NONAUTH_STA )
			{
				ignore_received_deauth = 1;
			} else if (WLAN_REASON_PREV_AUTH_NOT_VALID == reason) {
				// TODO: 802.11r
				ignore_received_deauth = 1;
			}
		}

		DBG_871X_LEVEL(_drv_always_, FUNC_ADPT_FMT" reason=%u, ta=%pM, ignore=%d\n"
			, FUNC_ADPT_ARG(padapter), reason, GetAddr2Ptr(pframe), ignore_received_deauth);

		if ( 0 == ignore_received_deauth )
		{
			receive_disconnect(padapter, GetAddr2Ptr(pframe), reason);
		}
	}
