#ifdef CONFIG_STA_MODE_SCAN_UNDER_AP_MODE
if((padapter->pbuddy_adapter->mlmeextpriv.mlmext_info.state&0x03) == WIFI_FW_AP_STATE)
		{
			if(IsSupported5G(padapter->registrypriv.wireless_mode) 
				&& IsSupported24G(padapter->registrypriv.wireless_mode)) //dual band
				mlme_set_scan_to_timer(pmlmepriv, CONC_SCANNING_TIMEOUT_DUAL_BAND);
			else //single band
				mlme_set_scan_to_timer(pmlmepriv, CONC_SCANNING_TIMEOUT_SINGLE_BAND);
		}		
		else
#endif //CONFIG_STA_MODE_SCAN_UNDER_AP_MODE
			mlme_set_scan_to_timer(pmlmepriv, SCANNING_TIMEOUT);
