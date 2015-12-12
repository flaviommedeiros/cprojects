static struct platform_device *devices[] __initdata = {
#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
	&palmld_pxa_keys,
#endif
	&palmld_backlight,
	&palmld_leds,
	&power_supply,
	&palmld_asoc,
	&palmld_hdd,
	&palmld_flash,
};
