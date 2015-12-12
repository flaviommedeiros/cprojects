static struct resource bfin_uart3_resources[] = {
	{
		.start = UART3_DLL,
		.end = UART3_RBR+2,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART3_TX,
		.end = IRQ_UART3_TX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART3_RX,
		.end = IRQ_UART3_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART3_ERROR,
		.end = IRQ_UART3_ERROR,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART3_TX,
		.end = CH_UART3_TX,
		.flags = IORESOURCE_DMA,
	},
	{
		.start = CH_UART3_RX,
		.end = CH_UART3_RX,
		.flags = IORESOURCE_DMA,
	},
#ifdef CONFIG_BFIN_UART3_CTSRTS
	{	/* CTS pin -- 0 means not supported */
		.start = GPIO_PB3,
		.end = GPIO_PB3,
		.flags = IORESOURCE_IO,
	},
	{	/* RTS pin -- 0 means not supported */
		.start = GPIO_PB2,
		.end = GPIO_PB2,
		.flags = IORESOURCE_IO,
	},
#endif
};
