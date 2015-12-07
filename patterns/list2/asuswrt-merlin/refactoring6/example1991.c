if ((nvram_match("wl0_radio", "1") || nvram_match("wl1_radio", "1")
#if defined(RTAC3200) || defined(RTAC5300)
		|| nvram_match("wl2_radio", "1")
#endif
	)
#ifdef RTCONFIG_LED_BTN
		&& nvram_get_int("AllLED")
#endif
	)
		led_control(LED_TURBO, LED_ON);
	else
		led_control(LED_TURBO, LED_OFF);
