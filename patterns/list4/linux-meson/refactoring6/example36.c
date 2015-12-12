if ((padapter->bSurpriseRemoved == _TRUE) 
		|| (padapter->bDriverStopped == _TRUE)
#ifdef CONFIG_CONCURRENT_MODE
		||((padapter->pbuddy_adapter) 
		&& ((padapter->pbuddy_adapter->bSurpriseRemoved) ||(padapter->pbuddy_adapter->bDriverStopped)))
#endif
	){
		RT_TRACE(_module_hal_xmit_c_, _drv_notice_,
			 ("%s: bSurpriseRemoved(wirte port)\n", __FUNCTION__));
		goto free_xmitbuf;
	}
