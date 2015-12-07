#if !defined(CONFIG_BCMWL5)
if(nvram_get_int("sw_mode")!=2)
#endif
	load_wifi_driver();
