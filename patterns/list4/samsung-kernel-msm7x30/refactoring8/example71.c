static struct samsung_gpio_chip s3c64xx_gpios_2bit[] = {
#ifdef CONFIG_PLAT_S3C64XX
	{
		.base	= S3C64XX_GPF_BASE,
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPF(0),
			.ngpio	= S3C64XX_GPIO_F_NR,
			.label	= "GPF",
		},
	}, {
		.config	= &samsung_gpio_cfgs[7],
		.chip	= {
			.base	= S3C64XX_GPI(0),
			.ngpio	= S3C64XX_GPIO_I_NR,
			.label	= "GPI",
		},
	}, {
		.config	= &samsung_gpio_cfgs[7],
		.chip	= {
			.base	= S3C64XX_GPJ(0),
			.ngpio	= S3C64XX_GPIO_J_NR,
			.label	= "GPJ",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPO(0),
			.ngpio	= S3C64XX_GPIO_O_NR,
			.label	= "GPO",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPP(0),
			.ngpio	= S3C64XX_GPIO_P_NR,
			.label	= "GPP",
		},
	}, {
		.config	= &samsung_gpio_cfgs[6],
		.chip	= {
			.base	= S3C64XX_GPQ(0),
			.ngpio	= S3C64XX_GPIO_Q_NR,
			.label	= "GPQ",
		},
	}, {
		.base	= S3C64XX_GPN_BASE,
		.irq_base = IRQ_EINT(0),
		.config	= &samsung_gpio_cfgs[5],
		.chip	= {
			.base	= S3C64XX_GPN(0),
			.ngpio	= S3C64XX_GPIO_N_NR,
			.label	= "GPN",
			.to_irq = samsung_gpiolib_to_irq,
		},
	},
#endif
};
