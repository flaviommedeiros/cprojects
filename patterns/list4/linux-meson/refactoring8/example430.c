static struct platform_device *platform_devices[] __initdata = {
	&cpuat91_norflash,
#ifdef CONFIG_MTD_PLATRAM
	&at91_sram,
#endif /* CONFIG_MTD_PLATRAM */
};
