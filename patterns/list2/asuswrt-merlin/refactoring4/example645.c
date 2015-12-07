#ifdef RTCONFIG_LED_BTN
if (!button_pressed(BTN_LED))
#else
		if ((!nvram_match("cpurev", "c0") && button_pressed(BTN_LED)) ||
			(nvram_match("cpurev", "c0") && !button_pressed(BTN_LED)))
#endif
		{
			TRACE_PT("button LED pressed\n");
			nvram_set("btn_led", "1");
		}
#if defined(RTAC68U)
		else if (!nvram_match("cpurev", "c0"))
		{
			TRACE_PT("button LED released\n");
			nvram_set("btn_led", "0");
		}
