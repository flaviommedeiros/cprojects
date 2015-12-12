static struct resource bfin_uart1_resources[] = {
	{
		.start = UART1_REVID,
		.end = UART1_RXDIV+4,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART1_TX,
		.end = IRQ_UART1_TX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART1_RX,
		.end = IRQ_UART1_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART1_STAT,
		.end = IRQ_UART1_STAT,
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
	{	/* CTS pin -- 0 means not supported */
		.start = GPIO_PG13,
		.end = GPIO_PG13,
		.flags = IORESOURCE_IO,
	},
	{	/* RTS pin -- 0 means not supported */
		.start = GPIO_PG10,
		.end = GPIO_PG10,
		.flags = IORESOURCE_IO,
	},
#endif
};
