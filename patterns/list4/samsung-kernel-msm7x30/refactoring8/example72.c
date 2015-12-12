static struct samsung_gpio_chip s5p6440_gpios_4bit[] = {
#ifdef CONFIG_CPU_S5P6440
	{
		.chip	= {
			.base	= S5P6440_GPA(0),
			.ngpio	= S5P6440_GPIO_A_NR,
			.label	= "GPA",
		},
	}, {
		.chip	= {
			.base	= S5P6440_GPB(0),
			.ngpio	= S5P6440_GPIO_B_NR,
			.label	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S5P6440_GPC(0),
			.ngpio	= S5P6440_GPIO_C_NR,
			.label	= "GPC",
		},
	}, {
		.base	= S5P64X0_GPG_BASE,
		.chip	= {
			.base	= S5P6440_GPG(0),
			.ngpio	= S5P6440_GPIO_G_NR,
			.label	= "GPG",
		},
	},
#endif
};
