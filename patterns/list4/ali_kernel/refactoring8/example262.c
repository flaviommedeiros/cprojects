static struct gpio_led ek_leds[] = {
	{	/* "top" led, red, powerled */
		.name			= "d8",
		.gpio			= AT91_PIN_PD30,
		.default_trigger	= "heartbeat",
	},
	{	/* "left" led, green, userled2, pwm3 */
		.name			= "d6",
		.gpio			= AT91_PIN_PD0,
		.active_low		= 1,
		.default_trigger	= "nand-disk",
	},
#if !(defined(CONFIG_LEDS_ATMEL_PWM) || defined(CONFIG_LEDS_ATMEL_PWM_MODULE))
	{	/* "right" led, green, userled1, pwm1 */
		.name			= "d7",
		.gpio			= AT91_PIN_PD31,
		.active_low		= 1,
		.default_trigger	= "mmc0",
	},
#endif
};
