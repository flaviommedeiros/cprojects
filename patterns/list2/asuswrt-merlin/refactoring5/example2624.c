#ifdef RTCONFIG_WPS_ENROLLEE
if (nvram_match("wps_enrollee", "1"))
		start_wsc_enrollee();
	else
#endif
		start_wsc();
