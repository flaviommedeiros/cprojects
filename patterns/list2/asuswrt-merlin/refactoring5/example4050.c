#ifdef RTCONFIG_DUALWAN
if(!strcmp(dualwan_mode, "lb") || !strcmp(dualwan_mode, "fb"))
		sprintf(log_title, "WAN(%d) Connection", wan_unit);
	else
#endif
		strcpy(log_title, "WAN Connection");
