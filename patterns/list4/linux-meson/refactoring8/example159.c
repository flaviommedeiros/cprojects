static struct samsung_gpio_chip s5pc100_gpios_4bit[] = {
#ifdef CONFIG_CPU_S5PC100
	{
		.chip	= {
			.base	= S5PC100_GPA0(0),
			.ngpio	= S5PC100_GPIO_A0_NR,
			.label	= "GPA0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPA1(0),
			.ngpio	= S5PC100_GPIO_A1_NR,
			.label	= "GPA1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPB(0),
			.ngpio	= S5PC100_GPIO_B_NR,
			.label	= "GPB",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPC(0),
			.ngpio	= S5PC100_GPIO_C_NR,
			.label	= "GPC",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPD(0),
			.ngpio	= S5PC100_GPIO_D_NR,
			.label	= "GPD",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPE0(0),
			.ngpio	= S5PC100_GPIO_E0_NR,
			.label	= "GPE0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPE1(0),
			.ngpio	= S5PC100_GPIO_E1_NR,
			.label	= "GPE1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPF0(0),
			.ngpio	= S5PC100_GPIO_F0_NR,
			.label	= "GPF0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPF1(0),
			.ngpio	= S5PC100_GPIO_F1_NR,
			.label	= "GPF1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPF2(0),
			.ngpio	= S5PC100_GPIO_F2_NR,
			.label	= "GPF2",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPF3(0),
			.ngpio	= S5PC100_GPIO_F3_NR,
			.label	= "GPF3",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPG0(0),
			.ngpio	= S5PC100_GPIO_G0_NR,
			.label	= "GPG0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPG1(0),
			.ngpio	= S5PC100_GPIO_G1_NR,
			.label	= "GPG1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPG2(0),
			.ngpio	= S5PC100_GPIO_G2_NR,
			.label	= "GPG2",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPG3(0),
			.ngpio	= S5PC100_GPIO_G3_NR,
			.label	= "GPG3",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPI(0),
			.ngpio	= S5PC100_GPIO_I_NR,
			.label	= "GPI",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPJ0(0),
			.ngpio	= S5PC100_GPIO_J0_NR,
			.label	= "GPJ0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPJ1(0),
			.ngpio	= S5PC100_GPIO_J1_NR,
			.label	= "GPJ1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPJ2(0),
			.ngpio	= S5PC100_GPIO_J2_NR,
			.label	= "GPJ2",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPJ3(0),
			.ngpio	= S5PC100_GPIO_J3_NR,
			.label	= "GPJ3",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPJ4(0),
			.ngpio	= S5PC100_GPIO_J4_NR,
			.label	= "GPJ4",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPK0(0),
			.ngpio	= S5PC100_GPIO_K0_NR,
			.label	= "GPK0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPK1(0),
			.ngpio	= S5PC100_GPIO_K1_NR,
			.label	= "GPK1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPK2(0),
			.ngpio	= S5PC100_GPIO_K2_NR,
			.label	= "GPK2",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPK3(0),
			.ngpio	= S5PC100_GPIO_K3_NR,
			.label	= "GPK3",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPL0(0),
			.ngpio	= S5PC100_GPIO_L0_NR,
			.label	= "GPL0",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPL1(0),
			.ngpio	= S5PC100_GPIO_L1_NR,
			.label	= "GPL1",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPL2(0),
			.ngpio	= S5PC100_GPIO_L2_NR,
			.label	= "GPL2",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPL3(0),
			.ngpio	= S5PC100_GPIO_L3_NR,
			.label	= "GPL3",
		},
	}, {
		.chip	= {
			.base	= S5PC100_GPL4(0),
			.ngpio	= S5PC100_GPIO_L4_NR,
			.label	= "GPL4",
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC00),
		.irq_base = IRQ_EINT(0),
		.chip	= {
			.base	= S5PC100_GPH0(0),
			.ngpio	= S5PC100_GPIO_H0_NR,
			.label	= "GPH0",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC20),
		.irq_base = IRQ_EINT(8),
		.chip	= {
			.base	= S5PC100_GPH1(0),
			.ngpio	= S5PC100_GPIO_H1_NR,
			.label	= "GPH1",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC40),
		.irq_base = IRQ_EINT(16),
		.chip	= {
			.base	= S5PC100_GPH2(0),
			.ngpio	= S5PC100_GPIO_H2_NR,
			.label	= "GPH2",
			.to_irq = samsung_gpiolib_to_irq,
		},
	}, {
		.base	= (S5P_VA_GPIO + 0xC60),
		.irq_base = IRQ_EINT(24),
		.chip	= {
			.base	= S5PC100_GPH3(0),
			.ngpio	= S5PC100_GPIO_H3_NR,
			.label	= "GPH3",
			.to_irq = samsung_gpiolib_to_irq,
		},
	},
#endif
};
