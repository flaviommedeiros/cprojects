if (adapter->mlmepriv.LinkDetectInfo.bBusyTraffic == _TRUE
		#ifdef CONFIG_CONCURRENT_MODE
		|| (adapter->pbuddy_adapter && adapter->pbuddy_adapter->mlmepriv.LinkDetectInfo.bBusyTraffic == _TRUE)
		#endif
	)
			busy_traffic = _TRUE;
