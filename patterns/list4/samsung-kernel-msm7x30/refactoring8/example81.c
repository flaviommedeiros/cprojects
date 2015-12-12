static struct samsung_gpio_chip s5pv210_gpios_4bit[] = {
#ifdef CONFIG_CPU_S5PV210
	{
		.chip	= {
			.base	= S5PV210_GPA0(0),
			.ngpio	= S5PV210_GPIO_A0_NR,
			.label	= "GPA0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPA1(0),
			.ngpio	= S5PV210_GPIO_A1_NR,
			.label	= "GPA1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPB(0),
			.ngpio	= S5PV210_GPIO_B_NR,
			.label	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPC0(0),
			.ngpio	= S5PV210_GPIO_C0_NR,
			.label	= "GPC0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPC1(0),
			.ngpio	= S5PV210_GPIO_C1_NR,
			.label	= "GPC1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPD0(0),
			.ngpio	= S5PV210_GPIO_D0_NR,
			.label	= "GPD0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPD1(0),
			.ngpio	= S5PV210_GPIO_D1_NR,
			.label	= "GPD1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPE0(0),
			.ngpio	= S5PV210_GPIO_E0_NR,
			.label	= "GPE0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPE1(0),
			.ngpio	= S5PV210_GPIO_E1_NR,
			.label	= "GPE1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPF0(0),
			.ngpio	= S5PV210_GPIO_F0_NR,
			.label	= "GPF0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPF1(0),
			.ngpio	= S5PV210_GPIO_F1_NR,
			.label	= "GPF1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPF2(0),
			.ngpio	= S5PV210_GPIO_F2_NR,
			.label	= "GPF2",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPF3(0),
			.ngpio	= S5PV210_GPIO_F3_NR,
			.label	= "GPF3",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPG0(0),
			.ngpio	= S5PV210_GPIO_G0_NR,
			.label	= "GPG0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPG1(0),
			.ngpio	= S5PV210_GPIO_G1_NR,
			.label	= "GPG1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPG2(0),
			.ngpio	= S5PV210_GPIO_G2_NR,
			.label	= "GPG2",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPG3(0),
			.ngpio	= S5PV210_GPIO_G3_NR,
			.label	= "GPG3",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPI(0),
			.ngpio	= S5PV210_GPIO_I_NR,
			.label	= "GPI",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPJ0(0),
			.ngpio	= S5PV210_GPIO_J0_NR,
			.label	= "GPJ0",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPJ1(0),
			.ngpio	= S5PV210_GPIO_J1_NR,
			.label	= "GPJ1",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPJ2(0),
			.ngpio	= S5PV210_GPIO_J2_NR,
			.label	= "GPJ2",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPJ3(0),
			.ngpio	= S5PV210_GPIO_J3_NR,
			.label	= "GPJ3",
		},
	}, {
		.chip	= {
			.base	= S5PV210_GPJ4(0),
			.ngpio	= S5PV210_GPIO_J4_NR,
			.label	= "GPJ4",
		},
	}, {
		.chip	= {
			.base	= S5PV210_MP01(0),
			.ngpio	= S5PV210_GPIO_MP01_NR,
			.label	= "MP01",
		},
	}, {
		.chip	= {
			.base	= S5PV210_MP02(0),
			.ngpio	= S5PV210_GPIO_MP02_NR,
			.label	= "MP02",
		},
	}, {
		.chip	= {
			.base	= S5PV210_MP03(0),
			.ngpio	= S5PV210_GPIO_MP03_NR,
			.label	= "MP03",
		},
	}, {
		.chip	= {
			.base	= S5PV210_MP04(0),
			.ngpio	= S5PV210_GPIO_MP04_NR,
			.label	= "MP04",
		},
	}, {
		.chip	= {
			.base	= S5PV210_MP05(0),
			.ngpio	= S5PV210_GPIO_MP05_NR,
			.label	= "MP05",
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC00),
		.irq_base = IRQ_EINT(0),
		.chip	= {
			.base	= S5PV210_GPH0(0),
			.ngpio	= S5PV210_GPIO_H0_NR,
			.label	= "GPH0",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC20),
		.irq_base = IRQ_EINT(8),
		.chip	= {
			.base	= S5PV210_GPH1(0),
			.ngpio	= S5PV210_GPIO_H1_NR,
			.label	= "GPH1",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC40),
		.irq_base = IRQ_EINT(16),
		.chip	= {
			.base	= S5PV210_GPH2(0),
			.ngpio	= S5PV210_GPIO_H2_NR,
			.label	= "GPH2",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC60),
		.irq_base = IRQ_EINT(24),
		.chip	= {
			.base	= S5PV210_GPH3(0),
			.ngpio	= S5PV210_GPIO_H3_NR,
			.label	= "GPH3",
			.to_irq = samsung_gpiolib_to_irq,
		},
	},
#endif
};
