static struct resource bfin_uart0_resources[] = {
	{
		.start = UART0_REVID,
		.end = UART0_RXDIV+4,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART0_TX,
		.end = IRQ_UART0_TX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART0_RX,
		.end = IRQ_UART0_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART0_STAT,
		.end = IRQ_UART0_STAT,
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
	{	/* CTS pin -- 0 means not supported */
		.start = GPIO_PD10,
		.end = GPIO_PD10,
		.flags = IORESOURCE_IO,
	},
	{	/* RTS pin -- 0 means not supported */
		.start = GPIO_PD9,
		.end = GPIO_PD9,
		.flags = IORESOURCE_IO,
	},
#endif
};
