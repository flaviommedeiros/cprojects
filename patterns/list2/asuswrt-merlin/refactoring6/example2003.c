if(nvram_match("asus_mfg", "0")
#if defined(RTCONFIG_LED_BTN) || defined(RTCONFIG_WPS_ALLLED_BTN)
		&& nvram_get_int("AllLED")
#endif
	)

	service_check();
