static struct nuc900fb_mach_info nuc900_fb_info = {
#if defined(CONFIG_GPM1040A0_320X240)
	.displays		= &nuc900_lcd_info[0],
#else
	.displays		= nuc900_lcd_info,
#endif
	.num_displays		= ARRAY_SIZE(nuc900_lcd_info),
	.default_display	= 0,
	.gpio_dir		= 0x00000004,
	.gpio_dir_mask		= 0xFFFFFFFD,
	.gpio_data		= 0x00000004,
	.gpio_data_mask		= 0xFFFFFFFD,
};
