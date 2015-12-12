static const struct gpio_led gpio_leds[] __initconst = {
	{
		.name		 = "camera",
		.gpio		 = LATCH1_GPIO_BASE + 0,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
#ifdef CONFIG_LEDS_TRIGGERS
		.default_trigger = "ams_delta_camera",
#endif
	},
	{
		.name		 = "advert",
		.gpio		 = LATCH1_GPIO_BASE + 1,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
	},
	{
		.name		 = "email",
		.gpio		 = LATCH1_GPIO_BASE + 2,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
	},
	{
		.name		 = "handsfree",
		.gpio		 = LATCH1_GPIO_BASE + 3,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
	},
	{
		.name		 = "voicemail",
		.gpio		 = LATCH1_GPIO_BASE + 4,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
	},
	{
		.name		 = "voice",
		.gpio		 = LATCH1_GPIO_BASE + 5,
		.default_state	 = LEDS_GPIO_DEFSTATE_OFF,
	},
};
