#if defined(RTCONFIG_LED_BTN) || defined(RTCONFIG_WPS_ALLLED_BTN)
if (nvram_get_int("AllLED"))
#endif
	{
		if (strcmp(usb_path1, "storage") && strcmp(usb_path2, "storage"))
		{
			no_blink(sig);
		}
		else
		{
			int led_id = nvram_get_int("usb_led_id");

			if (led_id != LED_USB && led_id != LED_USB3)
				led_id = LED_USB;

			count = (count+1) % 20;
			/* 0123456710 */
			/* 1010101010 */
			if (((count % 2) == 0) && (count > 8))
				led_control(led_id, LED_ON);
			else
				led_control(led_id, LED_OFF);
			alarmtimer(0, USBLED_URGENT_PERIOD);
		}
	}
