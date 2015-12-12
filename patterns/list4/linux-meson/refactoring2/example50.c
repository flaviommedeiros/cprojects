#ifdef CONFIG_XMIT_THREAD_MODE
if(padapter->adapter_type == PRIMARY_ADAPTER)
#endif  //SDIO_HCI + CONCURRENT
	{
	_rtw_up_sema(&padapter->xmitpriv.xmit_sema);
	_rtw_down_sema(&padapter->xmitpriv.terminate_xmitthread_sema);
	}
