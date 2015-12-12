#ifdef CONFIG_AUTOSUSPEND
if(is_primary_adapter(padapter) && (!adapter_to_pwrctl(padapter)->bInternalAutoSuspend ))
#endif
		rtw_free_network_queue(padapter, _TRUE);
