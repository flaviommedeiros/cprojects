#ifdef RTCONFIG_DUALWAN
if(nvram_match("wans_mode", "lb"))
		unit = WAN_UNIT_FIRST;
	else
#endif
	unit = wan_primary_ifunit();
