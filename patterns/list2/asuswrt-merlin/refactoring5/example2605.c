#ifdef RTCONFIG_PARENTALCTRL
if(nvram_get_int("MULTIFILTER_ALL") != 0 && count_pc_rules() > 0)
		strcpy(chain, "PControls");
	else
#endif
	strcpy(chain, "FORWARD");
