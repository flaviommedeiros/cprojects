static struct platform_device *colibri_pxa270_devices[] __initdata = {
	&colibri_pxa270_flash_device,
#if defined(CONFIG_DM9000)
	&dm9000_device,
#endif
};
