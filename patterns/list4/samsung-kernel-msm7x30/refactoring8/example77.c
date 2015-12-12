static struct samsung_gpio_chip s5p6450_gpios_4bit2[] = {
#ifdef CONFIG_CPU_S5P6450
	{
		.base	= S5P64X0_GPG_BASE + 0x4,
		.chip	= {
			.base	= S5P6450_GPG(0),
			.ngpio	= S5P6450_GPIO_G_NR,
			.label	= "GPG",
		},
	}, {
		.base	= S5P64X0_GPH_BASE + 0x4,
		.chip	= {
			.base	= S5P6450_GPH(0),
			.ngpio	= S5P6450_GPIO_H_NR,
			.label	= "GPH",
		},
	},
#endif
};
