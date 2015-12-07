#ifdef RTCONFIG_DUALWAN
if(nvram_match("wans_mode", "lb"))
		add_multi_routes();
