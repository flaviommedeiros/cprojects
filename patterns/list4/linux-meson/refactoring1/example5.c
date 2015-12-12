if(check_fwstate(pmlmepriv, WIFI_STATION_STATE) && check_fwstate(pmlmepriv, _FW_LINKED))
	{	
		rtw_disassoc_cmd(padapter, 0, _FALSE);	
		//s2-2.  indicate disconnect to os
		rtw_indicate_disconnect(padapter);
	}
	#ifdef CONFIG_AP_MODE
	else if(check_fwstate(pmlmepriv, WIFI_AP_STATE))	
	{
		rtw_sta_flush(padapter);
	}
#endif
