static const iw_handler ray_handler[] = {
	[SIOCSIWCOMMIT - SIOCIWFIRST] = (iw_handler) ray_commit,
	[SIOCGIWNAME - SIOCIWFIRST] = (iw_handler) ray_get_name,
	[SIOCSIWFREQ - SIOCIWFIRST] = (iw_handler) ray_set_freq,
	[SIOCGIWFREQ - SIOCIWFIRST] = (iw_handler) ray_get_freq,
	[SIOCSIWMODE - SIOCIWFIRST] = (iw_handler) ray_set_mode,
	[SIOCGIWMODE - SIOCIWFIRST] = (iw_handler) ray_get_mode,
	[SIOCGIWRANGE - SIOCIWFIRST] = (iw_handler) ray_get_range,
#ifdef WIRELESS_SPY
	[SIOCSIWSPY - SIOCIWFIRST] = (iw_handler) iw_handler_set_spy,
	[SIOCGIWSPY - SIOCIWFIRST] = (iw_handler) iw_handler_get_spy,
	[SIOCSIWTHRSPY - SIOCIWFIRST] = (iw_handler) iw_handler_set_thrspy,
	[SIOCGIWTHRSPY - SIOCIWFIRST] = (iw_handler) iw_handler_get_thrspy,
#endif /* WIRELESS_SPY */
	[SIOCGIWAP - SIOCIWFIRST] = (iw_handler) ray_get_wap,
	[SIOCSIWESSID - SIOCIWFIRST] = (iw_handler) ray_set_essid,
	[SIOCGIWESSID - SIOCIWFIRST] = (iw_handler) ray_get_essid,
	[SIOCSIWRATE - SIOCIWFIRST] = (iw_handler) ray_set_rate,
	[SIOCGIWRATE - SIOCIWFIRST] = (iw_handler) ray_get_rate,
	[SIOCSIWRTS - SIOCIWFIRST] = (iw_handler) ray_set_rts,
	[SIOCGIWRTS - SIOCIWFIRST] = (iw_handler) ray_get_rts,
	[SIOCSIWFRAG - SIOCIWFIRST] = (iw_handler) ray_set_frag,
	[SIOCGIWFRAG - SIOCIWFIRST] = (iw_handler) ray_get_frag,
};
