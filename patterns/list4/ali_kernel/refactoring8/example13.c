static struct resource au1xpsc_psc1_res[] = {
	[0] = {
		.start	= CPHYSADDR(PSC1_BASE_ADDR),
		.end	= CPHYSADDR(PSC1_BASE_ADDR) + 0x000fffff,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
#ifdef CONFIG_SOC_AU1200
		.start	= AU1200_PSC1_INT,
		.end	= AU1200_PSC1_INT,
#elif defined(CONFIG_SOC_AU1550)
		.start	= AU1550_PSC1_INT,
		.end	= AU1550_PSC1_INT,
#endif
		.flags	= IORESOURCE_IRQ,
	},
	[2] = {
		.start	= DSCR_CMD0_PSC1_TX,
		.end	= DSCR_CMD0_PSC1_TX,
		.flags	= IORESOURCE_DMA,
	},
	[3] = {
		.start	= DSCR_CMD0_PSC1_RX,
		.end	= DSCR_CMD0_PSC1_RX,
		.flags	= IORESOURCE_DMA,
	},
};
