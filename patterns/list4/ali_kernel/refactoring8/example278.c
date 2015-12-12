static struct platform_device *devices[] __initdata = {
#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
	&palmt5_pxa_keys,
#endif
	&palmt5_backlight,
	&power_supply,
	&palmt5_asoc,
	&palmt5_gpio_vbus,
};
