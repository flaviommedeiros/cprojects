static struct resource s5p_uart4_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 4
	[0] = {
		.start	= S5P_PA_UART4,
		.end	= S5P_PA_UART4 + S5P_SZ_UART - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_UART4,
		.end	= IRQ_UART4,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
