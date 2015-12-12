static struct gpio_led trizeps4_led[] = {
#ifdef STATUS_LEDS_ON_STUART_PINS
	{
		.name = "led0:orange:heartbeat",	/* */
		.default_trigger = "heartbeat",
		.gpio = GPIO_HEARTBEAT_LED,
		.active_low = 1,
	},
	{
		.name = "led1:yellow:cpubusy",		/* */
		.default_trigger = "cpu-busy",
		.gpio = GPIO_SYS_BUSY_LED,
		.active_low = 1,
	},
#endif
};
