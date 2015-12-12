if (pmlmepriv->LinkDetectInfo.bBusyTraffic == _TRUE
#ifdef CONFIG_CONCURRENT_MODE
	|| rtw_get_buddy_bBusyTraffic(padapter) == _TRUE
#endif //CONFIG_CONCURRENT_MODE
	)
	{
		indicate_wx_scan_complete_event(padapter);
		goto exit;
	}
