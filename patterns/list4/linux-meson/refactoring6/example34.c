if (check_fwstate(pmlmepriv, (_FW_LINKED|WIFI_AP_STATE))
#ifdef CONFIG_CONCURRENT_MODE
			|| check_buddy_fwstate(padapter, (_FW_LINKED|WIFI_AP_STATE))
#endif
			)
		{
			// enable to rx data frame
			rtw_write16(padapter, REG_RXFLTMAP2, 0xFFFF);
		}
