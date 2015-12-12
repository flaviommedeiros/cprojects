#ifdef CONFIG_CONCURRENT_MODE
if(pbuddy_adapter)
	{
		if(adapter->net_closed == _TRUE && pbuddy_adapter->net_closed == _TRUE)
		{
			return;
		}		
	}
	else
#endif //CONFIG_CONCURRENT_MODE
	if(adapter->net_closed == _TRUE)
	{
		return;
	}
