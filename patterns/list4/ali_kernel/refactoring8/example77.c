static iw_handler ipw_priv_handler[] = {
	ipw_wx_set_powermode,
	ipw_wx_get_powermode,
	ipw_wx_set_wireless_mode,
	ipw_wx_get_wireless_mode,
	ipw_wx_set_preamble,
	ipw_wx_get_preamble,
	ipw_wx_reset,
	ipw_wx_sw_reset,
#ifdef CONFIG_IPW2200_MONITOR
	ipw_wx_set_monitor,
#endif
};
