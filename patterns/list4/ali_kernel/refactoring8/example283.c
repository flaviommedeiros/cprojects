static struct platform_device *devices[] __initdata = {
#if defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
	&palmtx_pxa_keys,
#endif
	&palmtx_backlight,
	&power_supply,
	&palmtx_asoc,
	&palmtx_gpio_vbus,
	&palmtx_flash,
	&palmtx_nand,
};
