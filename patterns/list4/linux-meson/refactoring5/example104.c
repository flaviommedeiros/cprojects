#ifdef CONFIG_CONCURRENT_MODE
if (padapter->adapter_type > PRIMARY_ADAPTER)
							_rtw_up_sema(&(padapter->pbuddy_adapter->xmitpriv.xmit_sema));
						else
	#endif
							_rtw_up_sema(&(pxmitpriv->xmit_sema));
