static struct resource bfin_uart2_resources[] = {
	{
		.start = UART2_DLL,
		.end = UART2_RBR+2,
		.flags = IORESOURCE_MEM,
	},
#ifdef CONFIG_EARLY_PRINTK
	{
		.start = PORTB_FER,
		.end = PORTB_FER+2,
		.flags = IORESOURCE_REG,
	},
#endif
	{
		.start = IRQ_UART2_TX,
		.end = IRQ_UART2_TX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART2_RX,
		.end = IRQ_UART2_RX,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART2_ERROR,
		.end = IRQ_UART2_ERROR,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART2_TX,
		.end = CH_UART2_TX,
		.flags = IORESOURCE_DMA,
	},
	{
		.start = CH_UART2_RX,
		.end = CH_UART2_RX,
		.flags = IORESOURCE_DMA,
	},
};
