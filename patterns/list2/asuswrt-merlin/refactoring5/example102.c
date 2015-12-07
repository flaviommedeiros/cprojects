#ifdef RTCONFIG_WPS_ENROLLEE
if (nvram_match("wps_enrollee", "1")) {
		stop_wsc_enrollee();
	}
	else
#endif
		stop_wsc();
