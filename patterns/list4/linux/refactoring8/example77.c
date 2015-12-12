static struct samsung_gpio_chip s3c64xx_gpios_4bit2[] = {
#ifdef CONFIG_ARCH_S3C64XX
	{
		.base	= S3C64XX_GPH_BASE + 0x4,
		.chip	= {
			.base	= S3C64XX_GPH(0),
			.ngpio	= S3C64XX_GPIO_H_NR,
			.label	= "GPH",
		},
	}, {
		.base	= S3C64XX_GPK_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[0],
		.chip	= {
			.base	= S3C64XX_GPK(0),
			.ngpio	= S3C64XX_GPIO_K_NR,
			.label	= "GPK",
		},
	}, {
		.base	= S3C64XX_GPL_BASE + 0x4,
		.config	= &samsung_gpio_cfgs[1],
		.chip	= {
			.base	= S3C64XX_GPL(0),
			.ngpio	= S3C64XX_GPIO_L_NR,
			.label	= "GPL",
			.to_irq = s3c64xx_gpiolib_lbank_to_irq,
		},
	},
#endif
};
