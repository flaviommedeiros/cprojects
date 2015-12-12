static struct led_info adp5520_leds[] = {
	{
		.name = "adp5520-led1",
		.default_trigger = "none",
		.flags = FLAG_ID_ADP5520_LED1_ADP5501_LED0 | LED_OFFT_600ms,
	},
#ifdef ADP5520_EN_ALL_LEDS
	{
		.name = "adp5520-led2",
		.default_trigger = "none",
		.flags = FLAG_ID_ADP5520_LED2_ADP5501_LED1,
	},
	{
		.name = "adp5520-led3",
		.default_trigger = "none",
		.flags = FLAG_ID_ADP5520_LED3_ADP5501_LED2,
	},
#endif
};
