static struct samsung_gpio_chip s5p6450_gpios_4bit[] = {
#ifdef CONFIG_CPU_S5P6450
	{
		.chip	= {
			.base	= S5P6450_GPA(0),
			.ngpio	= S5P6450_GPIO_A_NR,
			.label	= "GPA",
		},
	}, {
		.chip	= {
			.base	= S5P6450_GPB(0),
			.ngpio	= S5P6450_GPIO_B_NR,
			.label	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S5P6450_GPC(0),
			.ngpio	= S5P6450_GPIO_C_NR,
			.label	= "GPC",
		},
	}, {
		.chip	= {
			.base	= S5P6450_GPD(0),
			.ngpio	= S5P6450_GPIO_D_NR,
			.label	= "GPD",
		},
	}, {
		.base	= S5P6450_GPK_BASE,
		.chip	= {
			.base	= S5P6450_GPK(0),
			.ngpio	= S5P6450_GPIO_K_NR,
			.label	= "GPK",
		},
	},
#endif
};
