static struct platform_device *devices[] __initdata = {
#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
	&palmte2_pxa_keys,
#endif
	&palmte2_backlight,
	&power_supply,
	&palmte2_asoc,
	&palmte2_gpio_vbus,
};
