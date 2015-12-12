static struct gpio_led stk1000_j2_led[] = {
#ifdef CONFIG_BOARD_ATSTK1000_J2_LED8
#define LEDSTRING "J2 jumpered to LED8"
	{ .name = "led0:amber", .gpio = GPIO_PIN_PB( 8), },
	{ .name = "led1:amber", .gpio = GPIO_PIN_PB( 9), },
	{ .name = "led2:amber", .gpio = GPIO_PIN_PB(10), },
	{ .name = "led3:amber", .gpio = GPIO_PIN_PB(13), },
	{ .name = "led4:amber", .gpio = GPIO_PIN_PB(14), },
	{ .name = "led5:amber", .gpio = GPIO_PIN_PB(15), },
	{ .name = "led6:amber", .gpio = GPIO_PIN_PB(16), },
	{ .name = "led7:amber", .gpio = GPIO_PIN_PB(30),
			.default_trigger = "heartbeat", },
#else	/* RGB */
#define LEDSTRING "J2 jumpered to RGB LEDs"
	{ .name = "r1:red",     .gpio = GPIO_PIN_PB( 8), },
	{ .name = "g1:green",   .gpio = GPIO_PIN_PB(10), },
	{ .name = "b1:blue",    .gpio = GPIO_PIN_PB(14), },

	{ .name = "r2:red",     .gpio = GPIO_PIN_PB( 9),
			.default_trigger = "heartbeat", },
	{ .name = "g2:green",   .gpio = GPIO_PIN_PB(13), },
	{ .name = "b2:blue",    .gpio = GPIO_PIN_PB(15),
			.default_trigger = "heartbeat", },
	/* PB16, PB30 unused */
#endif
};
