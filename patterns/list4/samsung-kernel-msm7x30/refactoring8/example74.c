static struct samsung_gpio_chip s5p6440_gpios_rbank[] = {
#ifdef CONFIG_CPU_S5P6440
	{
		.base	= S5P64X0_GPR_BASE + 0x4,
		.config	= &s5p64x0_gpio_cfg_rbank,
		.chip	= {
			.base	= S5P6440_GPR(0),
			.ngpio	= S5P6440_GPIO_R_NR,
			.label	= "GPR",
		},
	},
#endif
};
