#ifdef CONFIG_CONCURRENT_MODE
if(padapter->iface_type == IFACE_PORT0) 
#endif
					rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_TRAFFIC_BUSY, 1);
