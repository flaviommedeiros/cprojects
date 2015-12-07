if (!is_routing_enabled()
#ifdef RTCONFIG_WIRELESSREPEATER
		&& nvram_get_int("sw_mode") != SW_MODE_REPEATER
#endif
	)
		return;
