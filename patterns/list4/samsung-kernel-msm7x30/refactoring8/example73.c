static struct samsung_gpio_chip s5p6440_gpios_4bit2[] = {
#ifdef CONFIG_CPU_S5P6440
	{
		.base	= S5P64X0_GPH_BASE + 0x4,
		.chip	= {
			.base	= S5P6440_GPH(0),
			.ngpio	= S5P6440_GPIO_H_NR,
			.label	= "GPH",
		},
	},
#endif
};
