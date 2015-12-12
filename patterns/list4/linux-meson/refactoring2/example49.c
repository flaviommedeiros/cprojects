#ifdef CONFIG_CONCURRENT_MODE
if(padapter->isprimary == _TRUE)
#endif //CONFIG_CONCURRENT_MODE
	{
		rtw_stop_cmd_thread(padapter);
	}
