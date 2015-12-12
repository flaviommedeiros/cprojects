#ifdef CONFIG_IOCTL_CFG80211
if(adapter_wdev_data(padapter)->p2p_enabled == _TRUE && pwdinfo->driver_interface == DRIVER_CFG80211 )
			initialgain = 0x30;
		else
#endif //CONFIG_IOCTL_CFG80211
		if ( !rtw_p2p_chk_state( pwdinfo, P2P_STATE_NONE ) )
			initialgain = 0x28;
		else
#endif //CONFIG_P2P
			initialgain = 0x1e;
