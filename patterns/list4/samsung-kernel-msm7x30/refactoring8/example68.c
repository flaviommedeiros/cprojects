struct samsung_gpio_chip s3c24xx_gpios[] = {
#ifdef CONFIG_PLAT_S3C24XX
	{
		.config	= &s3c24xx_gpiocfg_banka,
		.chip	= {
			.base			= S3C2410_GPA(0),
			.owner			= THIS_MODULE,
			.label			= "GPIOA",
			.ngpio			= 24,
			.direction_input	= s3c24xx_gpiolib_banka_input,
			.direction_output	= s3c24xx_gpiolib_banka_output,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPB(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOB",
			.ngpio	= 16,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPC(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOC",
			.ngpio	= 16,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPD(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOD",
			.ngpio	= 16,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPE(0),
			.label	= "GPIOE",
			.owner	= THIS_MODULE,
			.ngpio	= 16,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPF(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOF",
			.ngpio	= 8,
			.to_irq	= s3c24xx_gpiolib_fbank_to_irq,
		},
	}, {
		.irq_base = IRQ_EINT8,
		.chip	= {
			.base	= S3C2410_GPG(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOG",
			.ngpio	= 16,
			.to_irq	= samsung_gpiolib_to_irq,
		},
	}, {
		.chip	= {
			.base	= S3C2410_GPH(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOH",
			.ngpio	= 11,
		},
	},
		/* GPIOS for the S3C2443 and later devices. */
	{
		.base	= S3C2440_GPJCON,
		.chip	= {
			.base	= S3C2410_GPJ(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOJ",
			.ngpio	= 16,
		},
	}, {
		.base	= S3C2443_GPKCON,
		.chip	= {
			.base	= S3C2410_GPK(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOK",
			.ngpio	= 16,
		},
	}, {
		.base	= S3C2443_GPLCON,
		.chip	= {
			.base	= S3C2410_GPL(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOL",
			.ngpio	= 15,
		},
	}, {
		.base	= S3C2443_GPMCON,
		.chip	= {
			.base	= S3C2410_GPM(0),
			.owner	= THIS_MODULE,
			.label	= "GPIOM",
			.ngpio	= 2,
		},
	},
#endif
};
