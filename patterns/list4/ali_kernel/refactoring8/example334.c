static struct resource bfin_uart1_resources[] = {
	{
		.start = 0xFFC02000,
		.end = 0xFFC020FF,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART1_RX,
		.end = IRQ_UART1_RX+1,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART1_ERROR,
		.end = IRQ_UART1_ERROR,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART1_TX,
		.end = CH_UART1_TX,
		.flags = IORESOURCE_DMA,
	},
	{
		.start = CH_UART1_RX,
		.end = CH_UART1_RX,
		.flags = IORESOURCE_DMA,
	},
#ifdef CONFIG_BFIN_UART1_CTSRTS
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
