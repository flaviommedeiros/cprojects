if ((mode == LED_ON) && (nvram_get_int("led_disable") == 1) && (which != LED_TURBO)
#ifdef RTCONFIG_QTN
		&& (which != BTN_QTN_RESET)
#endif
	)
	{
		return 0;
	}
