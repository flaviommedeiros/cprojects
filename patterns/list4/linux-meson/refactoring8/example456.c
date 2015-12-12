static struct platform_device *devices[] __initdata = {
	&smc91x_device,
	&pcm027_flash,
#ifdef CONFIG_LEDS_GPIO
	&pcm027_led_dev
#endif
};
