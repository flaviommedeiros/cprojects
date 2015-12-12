static struct samsung_gpio_chip s5p6440_gpios_2bit[] = {
#ifdef CONFIG_CPU_S5P6440
	{
		.base	= S5P64X0_GPF_BASE,
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S5P6440_GPF(0),
			.ngpio	= S5P6440_GPIO_F_NR,
			.label	= "GPF",
		},
	}, {
		.base	= S5P64X0_GPI_BASE,
		.config	= &samsung_gpio_cfgs[4],
		.chip	= {
			.base	= S5P6440_GPI(0),
			.ngpio	= S5P6440_GPIO_I_NR,
			.label	= "GPI",
		},
	}, {
		.base	= S5P64X0_GPJ_BASE,
		.config	= &samsung_gpio_cfgs[4],
		.chip	= {
			.base	= S5P6440_GPJ(0),
			.ngpio	= S5P6440_GPIO_J_NR,
			.label	= "GPJ",
		},
	}, {
		.base	= S5P64X0_GPN_BASE,
		.config	= &samsung_gpio_cfgs[5],
		.chip	= {
			.base	= S5P6440_GPN(0),
			.ngpio	= S5P6440_GPIO_N_NR,
			.label	= "GPN",
		},
	}, {
		.base	= S5P64X0_GPP_BASE,
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S5P6440_GPP(0),
			.ngpio	= S5P6440_GPIO_P_NR,
			.label	= "GPP",
		},
	},
#endif
};
