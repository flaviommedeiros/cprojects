if ((check_fwstate(pmlmepriv, WIFI_AP_STATE) == _TRUE)
#ifdef CONFIG_CONCURRENT_MODE
		|| (check_buddy_fwstate(padapter, WIFI_AP_STATE) == _TRUE)
#endif
		)
	{
		rcr_clear_bit = RCR_CBSSID_BCN;
	}
#ifdef CONFIG_TDLS
	// TDLS will clear RCR_CBSSID_DATA bit for connection.
	else if (padapter->tdlsinfo.link_established == _TRUE)
	{
		rcr_clear_bit = RCR_CBSSID_BCN;
	}
