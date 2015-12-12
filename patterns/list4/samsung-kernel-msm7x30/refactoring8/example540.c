static struct resource s5p_uart5_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 5
	[0] = {
		.start	= S5P_PA_UART5,
		.end	= S5P_PA_UART5 + S5P_SZ_UART - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_UART5,
		.end	= IRQ_UART5,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
