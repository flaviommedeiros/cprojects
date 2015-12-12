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
		DBG_871X_LEVEL(_drv_always_, FUNC_ADPT_FMT" reason=%u, ta=%pM\n"
			, FUNC_ADPT_ARG(padapter), reason, GetAddr2Ptr(pframe));

		receive_disconnect(padapter, GetAddr2Ptr(pframe), reason);
	}
