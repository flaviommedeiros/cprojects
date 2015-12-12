static struct resource ax88796_resources[] = {
	{
#ifdef CONFIG_SH_R7780RP
		.start  = 0xa5800400,
		.end    = 0xa5800400 + (0x20 * 0x2) - 1,
#else
		.start  = 0xa4100400,
		.end    = 0xa4100400 + (0x20 * 0x2) - 1,
#endif
		.flags  = IORESOURCE_MEM,
	},
	{
		.start  = IRQ_AX88796,
		.end    = IRQ_AX88796,
		.flags  = IORESOURCE_IRQ,
	},
};
