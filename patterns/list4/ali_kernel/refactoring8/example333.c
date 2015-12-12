static struct resource bfin_uart0_resources[] = {
	{
		.start = 0xFFC00400,
		.end = 0xFFC004FF,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART0_RX,
		.end = IRQ_UART0_RX+1,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART0_ERROR,
		.end = IRQ_UART0_ERROR,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART0_TX,
		.end = CH_UART0_TX,
		.flags = IORESOURCE_DMA,
	},
	{
		.start = CH_UART0_RX,
		.end = CH_UART0_RX,
		.flags = IORESOURCE_DMA,
	},
#ifdef CONFIG_BFIN_UART0_CTSRTS
	{
		/*
		 * Refer to arch/blackfin/mach-xxx/include/mach/gpio.h for the GPIO map.
		 */
		.start = -1,
		.end = -1,
		.flags = IORESOURCE_IO,
	},
	{
		/*
		 * Refer to arch/blackfin/mach-xxx/include/mach/gpio.h for the GPIO map.
		 */
		.start = -1,
		.end = -1,
		.flags = IORESOURCE_IO,
	},
#endif
};
