static const iw_handler ray_handler[] = {
	IW_HANDLER(SIOCSIWCOMMIT, ray_commit),
	IW_HANDLER(SIOCGIWNAME, ray_get_name),
	IW_HANDLER(SIOCSIWFREQ, ray_set_freq),
	IW_HANDLER(SIOCGIWFREQ, ray_get_freq),
	IW_HANDLER(SIOCSIWMODE, ray_set_mode),
	IW_HANDLER(SIOCGIWMODE, ray_get_mode),
	IW_HANDLER(SIOCGIWRANGE, ray_get_range),
#ifdef WIRELESS_SPY
	IW_HANDLER(SIOCSIWSPY, iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY, iw_handler_get_spy),
	IW_HANDLER(SIOCSIWTHRSPY, iw_handler_set_thrspy),
	IW_HANDLER(SIOCGIWTHRSPY, iw_handler_get_thrspy),
#endif /* WIRELESS_SPY */
	IW_HANDLER(SIOCGIWAP, ray_get_wap),
	IW_HANDLER(SIOCSIWESSID, ray_set_essid),
	IW_HANDLER(SIOCGIWESSID, ray_get_essid),
	IW_HANDLER(SIOCSIWRATE, ray_set_rate),
	IW_HANDLER(SIOCGIWRATE, ray_get_rate),
	IW_HANDLER(SIOCSIWRTS, ray_set_rts),
	IW_HANDLER(SIOCGIWRTS, ray_get_rts),
	IW_HANDLER(SIOCSIWFRAG, ray_set_frag),
	IW_HANDLER(SIOCGIWFRAG, ray_get_frag),
};
