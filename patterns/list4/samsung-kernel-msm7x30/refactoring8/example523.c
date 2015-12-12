static struct plat_serial8250_port serial_platform_data[] = {
	{
		.membase	= (void*)SERIAL0_VIRT,
		.mapbase	= SERIAL0_BASE,
		.irq		= IRQ_UART0,
		.uartclk	= 2*1843200,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
	{
		.membase	= (void*)SERIAL1_VIRT,
		.mapbase	= SERIAL1_BASE,
		.irq		= IRQ_UART1,
		.uartclk	= 2*1843200,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
#ifdef CONFIG_H7202_SERIAL23
	{
		.membase	= (void*)SERIAL2_VIRT,
		.mapbase	= SERIAL2_BASE,
		.irq		= IRQ_UART2,
		.uartclk	= 2*1843200,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
	{
		.membase	= (void*)SERIAL3_VIRT,
		.mapbase	= SERIAL3_BASE,
		.irq		= IRQ_UART3,
		.uartclk	= 2*1843200,
		.regshift	= 2,
		.iotype		= UPIO_MEM,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
#endif
	{ },
};
