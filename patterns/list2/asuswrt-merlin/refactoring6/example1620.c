if (nvram_match("wl0_radio", "1") || nvram_match("wl1_radio", "1")
#ifdef RTAC3200
				|| nvram_match("wl2_radio", "1")
#endif
			)
				led_control(LED_TURBO, LED_ON);
