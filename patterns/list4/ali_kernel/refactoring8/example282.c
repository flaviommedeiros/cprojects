static struct plat_serial8250_port serial_platform_data[] = {
#ifndef CONFIG_SERIAL_PXA
	/* Internal UARTs */
	{
		.membase	= (void *)&FFUART,
		.mapbase	= __PREG(FFUART),
		.irq		= IRQ_FFUART,
		.uartclk	= 921600 * 16,
		.regshift	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	},
	{
		.membase	= (void *)&BTUART,
		.mapbase	= __PREG(BTUART),
		.irq		= IRQ_BTUART,
		.uartclk	= 921600 * 16,
		.regshift	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	},
	{
		.membase	= (void *)&STUART,
		.mapbase	= __PREG(STUART),
		.irq		= IRQ_STUART,
		.uartclk	= 921600 * 16,
		.regshift	= 2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
	},
	/* External UARTs */
	{
		.mapbase	= VIPER_UARTA_PHYS,
		.irq		= gpio_to_irq(VIPER_UARTA_GPIO),
		.uartclk	= 1843200,
		.regshift	= 1,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP |
				  UPF_SKIP_TEST,
	},
	{
		.mapbase	= VIPER_UARTB_PHYS,
		.irq		= gpio_to_irq(VIPER_UARTB_GPIO),
		.uartclk	= 1843200,
		.regshift	= 1,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_IOREMAP |
				  UPF_SKIP_TEST,
	},
#endif
	{ },
};
