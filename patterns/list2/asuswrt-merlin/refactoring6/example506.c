if (!usb_busy
#if defined(RTCONFIG_LED_BTN) || defined(RTCONFIG_WPS_ALLLED_BTN)
			&& nvram_get_int("AllLED")
#endif
			)
	{
#ifdef RTCONFIG_USB_XHCI
		if (have_usb3_led(model)) {
			if (model==MODEL_RTN18U && (nvram_match("bl_version", "3.0.0.7") || nvram_match("bl_version", "1.0.0.0")))
			{
				if ((got_usb2 != got_usb2_old) || (got_usb3 != got_usb3_old)) {
					if (!got_usb2 && !got_usb3)
						led_control(LED_USB, LED_OFF);
					else
						led_control(LED_USB, LED_ON);
				}
			}
			else {
				if (got_usb2 != got_usb2_old) {
					if (got_usb2)
						led_control(LED_USB, LED_ON);
					else
						led_control(LED_USB, LED_OFF);
				}
				if (got_usb3 != got_usb3_old) {
					if (got_usb3)
						led_control(LED_USB3, LED_ON);
					else
						led_control(LED_USB3, LED_OFF);
				}
			}
		}
		else
#endif
		if (status_usb != status_usb_old)
		{
			if (status_usb)
				led_control(LED_USB, LED_ON);
			else
				led_control(LED_USB, LED_OFF);
		}
	}
	else
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
