if ((adapter_to_pwrctl(adapter)->bFwCurrentInPSMode ==_TRUE )
#ifdef CONFIG_BT_COEXIST
		&& (rtw_btcoex_IsBtControlLps(adapter) == _FALSE)
#endif		
		) 
	{
		u8 bEnterPS;	
		
		linked_status_chk(adapter, 1);	
			
		bEnterPS = traffic_status_watchdog(adapter, 1);
		if(bEnterPS)
		{
			//rtw_lps_ctrl_wk_cmd(adapter, LPS_CTRL_ENTER, 1);
			rtw_hal_dm_watchdog_in_lps(adapter);
		}
		else
		{
			//call rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1) in traffic_status_watchdog()
		}
			
	}
	else
#endif //CONFIG_LPS_LCLK_WD_TIMER	
	{
		if(is_primary_adapter(adapter))
		{	
			rtw_dynamic_chk_wk_cmd(adapter);		
		}	
	}
