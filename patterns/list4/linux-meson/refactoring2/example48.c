#ifdef CONFIG_XMIT_THREAD_MODE
if(is_primary_adapter(padapter))
#endif		
	{
		padapter->xmitThread = kthread_run(rtw_xmit_thread, padapter, "RTW_XMIT_THREAD");
		if(IS_ERR(padapter->xmitThread))
			_status = _FAIL;
	}
