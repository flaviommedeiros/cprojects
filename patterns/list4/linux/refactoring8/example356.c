static struct plat_serial8250_port uart8250_data[] = {
	SMC_PORT(0x3F8, 4),
	SMC_PORT(0x2F8, 3),
#ifndef CONFIG_MIPS_CMP
	{
		.mapbase	= 0x1f000900,	/* The CBUS UART */
		.irq		= MIPS_CPU_IRQ_BASE + MIPSCPU_INT_MB2,
		.uartclk	= 3686400,	/* Twice the usual clk! */
		.iotype		= UPIO_MEM32,
		.flags		= CBUS_UART_FLAGS,
		.regshift	= 3,
	},
#endif
	{ },
};
