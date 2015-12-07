#ifdef RTCONFIG_WPS_ENROLLEE
if (nvram_match("wps_enrollee", "1"))
			strcpy(status, getWscStatus_enrollee(i));
		else
#endif
			strcpy(status, getWscStatus(i));
