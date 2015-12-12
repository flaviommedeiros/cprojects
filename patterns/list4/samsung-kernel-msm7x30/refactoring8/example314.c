static struct resource cf_ide_resources[] = {
	[0] = {
		.start	= PA_AREA5_IO + 0x1000,
		.end	= PA_AREA5_IO + 0x1000 + 0x10 - 0x2,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= PA_AREA5_IO + 0x80c,
		.end	= PA_AREA5_IO + 0x80c,
		.flags	= IORESOURCE_MEM,
	},
#ifndef CONFIG_RTS7751R2D_1 /* For R2D-1 polling is preferred */
	[2] = {
		.start	= IRQ_CF_IDE,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
