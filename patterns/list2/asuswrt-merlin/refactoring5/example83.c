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
