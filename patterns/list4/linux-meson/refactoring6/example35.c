if ((padapter->bSurpriseRemoved == _TRUE) 
			|| (padapter->bDriverStopped == _TRUE)
#ifdef CONFIG_CONCURRENT_MODE
			||((padapter->pbuddy_adapter) 
		&& ((padapter->pbuddy_adapter->bSurpriseRemoved) ||(padapter->pbuddy_adapter->bDriverStopped)))
#endif		
		){
			DBG_871X("%s: bSurpriseRemoved or bDriverStopped (wait TxOQT)\n", __func__);
			return _FALSE;
		}
