static struct resource lcdc_resources[] = {
	[0] = {
		.start	= AT91SAM9261_LCDC_BASE,
		.end	= AT91SAM9261_LCDC_BASE + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= NR_IRQS_LEGACY + AT91SAM9261_ID_LCDC,
		.end	= NR_IRQS_LEGACY + AT91SAM9261_ID_LCDC,
		.flags	= IORESOURCE_IRQ,
	},
#if defined(CONFIG_FB_INTSRAM)
	[2] = {
		.start	= AT91SAM9261_SRAM_BASE,
		.end	= AT91SAM9261_SRAM_BASE + AT91SAM9261_SRAM_SIZE - 1,
		.flags	= IORESOURCE_MEM,
	},
#endif
};
