static const iw_handler wl_handler[] =
{
	IW_HANDLER(SIOCSIWCOMMIT, (iw_handler) wireless_commit),
	IW_HANDLER(SIOCGIWNAME, (iw_handler) wireless_get_protocol),
	IW_HANDLER(SIOCSIWFREQ, (iw_handler) wireless_set_frequency),
	IW_HANDLER(SIOCGIWFREQ, (iw_handler) wireless_get_frequency),
	IW_HANDLER(SIOCSIWMODE, (iw_handler) wireless_set_porttype),
	IW_HANDLER(SIOCGIWMODE, (iw_handler) wireless_get_porttype),
	IW_HANDLER(SIOCSIWSENS, (iw_handler) wireless_set_sensitivity),
	IW_HANDLER(SIOCGIWSENS, (iw_handler) wireless_get_sensitivity),
	IW_HANDLER(SIOCGIWRANGE, (iw_handler) wireless_get_range),
	IW_HANDLER(SIOCSIWSPY, iw_handler_set_spy),
	IW_HANDLER(SIOCGIWSPY, iw_handler_get_spy),
#if 1 //;? (HCF_TYPE) & HCF_TYPE_STA
	IW_HANDLER(SIOCGIWAP, (iw_handler) wireless_get_bssid),
#endif
	IW_HANDLER(SIOCGIWAPLIST, (iw_handler) wireless_get_ap_list),
	IW_HANDLER(SIOCSIWSCAN, (iw_handler) wireless_set_scan),
	IW_HANDLER(SIOCGIWSCAN, (iw_handler) wireless_get_scan),
	IW_HANDLER(SIOCSIWESSID, (iw_handler) wireless_set_essid),
	IW_HANDLER(SIOCGIWESSID, (iw_handler) wireless_get_essid),
	IW_HANDLER(SIOCSIWNICKN, (iw_handler) wireless_set_nickname),
	IW_HANDLER(SIOCGIWNICKN, (iw_handler) wireless_get_nickname),
	IW_HANDLER(SIOCSIWRATE, (iw_handler) wireless_set_rate),
	IW_HANDLER(SIOCGIWRATE, (iw_handler) wireless_get_rate),
	IW_HANDLER(SIOCSIWRTS, (iw_handler) wireless_set_rts_threshold),
	IW_HANDLER(SIOCGIWRTS, (iw_handler) wireless_get_rts_threshold),
	IW_HANDLER(SIOCGIWTXPOW, (iw_handler) wireless_get_tx_power),
	IW_HANDLER(SIOCSIWENCODE, (iw_handler) wireless_set_encode),
	IW_HANDLER(SIOCGIWENCODE, (iw_handler) wireless_get_encode),
	IW_HANDLER(SIOCSIWPOWER, (iw_handler) wireless_set_power),
	IW_HANDLER(SIOCGIWPOWER, (iw_handler) wireless_get_power),
	IW_HANDLER(SIOCSIWGENIE, (iw_handler) wireless_set_genie),
	IW_HANDLER(SIOCSIWAUTH, (iw_handler) wireless_set_auth),
	IW_HANDLER(SIOCSIWENCODEEXT, (iw_handler) wireless_set_encodeext),
};