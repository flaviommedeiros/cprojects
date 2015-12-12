static struct resource s5p_uart3_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 3
	[0] = {
		.start	= S5P_PA_UART3,
		.end	= S5P_PA_UART3 + S5P_SZ_UART - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_UART3,
		.end	= IRQ_UART3,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
