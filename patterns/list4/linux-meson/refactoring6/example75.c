if ( rtw_p2p_chk_state(pwdinfo, P2P_STATE_NONE) 
#ifdef CONFIG_CONCURRENT_MODE
		|| (padapter->iface_type != IFACE_PORT0) 
#endif
		)
	{
		return res;
	}
