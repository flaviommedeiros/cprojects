#if (defined(PLN12) || defined(PLAC56))
if((gpio_pin = (use_gpio = nvram_get_int("led_pwr_red_gpio")) & 0xff) != 0xff)
#else
	if((gpio_pin = (use_gpio = nvram_get_int("led_pwr_gpio")) & 0xff) != 0xff)
#endif
	{
		enable = (use_gpio&GPIO_ACTIVE_LOW)==0 ? 1 : 0;
		set_gpio(gpio_pin, enable);
#ifdef RTCONFIG_INTERNAL_GOBI	// save setting value
		{ int i; char led[16]; for(i=0; i<LED_ID_MAX; i++) if(gpio_pin == (led_gpio_table[i]&0xff)){snprintf(led, sizeof(led), "led%02d", i); nvram_set_int(led, LED_ON); break;}}
#endif	/* RTCONFIG_INTERNAL_GOBI */
	}
