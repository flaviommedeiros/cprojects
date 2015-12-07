#ifdef RTCONFIG_DEFAULT_AP_MODE
if (nvram_get_int("sw_mode") != SW_MODE_ROUTER)
		system("rtkswitch 8 7"); // LLLLL
	else
#endif
	system("rtkswitch 8 0");
