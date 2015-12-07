#ifdef RTCONFIG_WLAN_LED
if (nvram_contains_word("rc_support", "led_2g"))
	{
#if defined(RTN53)
		if(nvram_get_int("wl0_radio") == 0)
			led_control(LED_2G, LED_OFF);
		else
#endif
		fake_wl_led_2g();
	}
