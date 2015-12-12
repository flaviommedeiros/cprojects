#ifdef TO_DO_LIST
if(Adapter->MgntInfo.mActingAsAp)
	{
		AP_dm_CheckRateAdaptive(dev);
		//return;
	}
	else
#endif
	{
		dm_check_rate_adaptive(dev);
	}
