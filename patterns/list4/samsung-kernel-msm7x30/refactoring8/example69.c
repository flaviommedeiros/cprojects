static struct samsung_gpio_chip s3c64xx_gpios_4bit[] = {
#ifdef CONFIG_PLAT_S3C64XX
	{
		.chip	= {
			.base	= S3C64XX_GPA(0),
			.ngpio	= S3C64XX_GPIO_A_NR,
			.label	= "GPA",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPB(0),
			.ngpio	= S3C64XX_GPIO_B_NR,
			.label	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPC(0),
			.ngpio	= S3C64XX_GPIO_C_NR,
			.label	= "GPC",
		},
	}, {
		.chip	= {
			.base	= S3C64XX_GPD(0),
			.ngpio	= S3C64XX_GPIO_D_NR,
			.label	= "GPD",
		},
	}, {
		.config	= &samsung_gpio_cfgs[0],
		.chip	= {
			.base	= S3C64XX_GPE(0),
			.ngpio	= S3C64XX_GPIO_E_NR,
			.label	= "GPE",
		},
	}, {
		.base	= S3C64XX_GPG_BASE,
		.chip	= {
			.base	= S3C64XX_GPG(0),
			.ngpio	= S3C64XX_GPIO_G_NR,
			.label	= "GPG",
		},
	}, {
		.base	= S3C64XX_GPM_BASE,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= {
			.base	= S3C64XX_GPM(0),
			.ngpio	= S3C64XX_GPIO_M_NR,
			.label	= "GPM",
			.to_irq = s3c64xx_gpiolib_mbank_to_irq,
		},
	},
#endif
};
