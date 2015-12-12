static struct resource bfin_uart0_resources[] = {
	{
		.start = UART0_DLL,
		.end = UART0_RBR+2,
		.flags = IORESOURCE_MEM,
	},
#ifdef CONFIG_EARLY_PRINTK
	{
		.start = PORTE_FER,
		.end = PORTE_FER+2,
		.flags = IORESOURCE_REG,
	},
#endif
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
};
