static struct map_desc ixp4xx_io_desc[] __initdata = {
	{	/* UART, Interrupt ctrl, GPIO, timers, NPEs, MACs, USB .... */
		.virtual	= IXP4XX_PERIPHERAL_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_PERIPHERAL_BASE_PHYS),
		.length		= IXP4XX_PERIPHERAL_REGION_SIZE,
		.type		= MT_DEVICE
	}, {	/* Expansion Bus Config Registers */
		.virtual	= IXP4XX_EXP_CFG_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_EXP_CFG_BASE_PHYS),
		.length		= IXP4XX_EXP_CFG_REGION_SIZE,
		.type		= MT_DEVICE
	}, {	/* PCI Registers */
		.virtual	= IXP4XX_PCI_CFG_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_PCI_CFG_BASE_PHYS),
		.length		= IXP4XX_PCI_CFG_REGION_SIZE,
		.type		= MT_DEVICE
	},
#ifdef CONFIG_DEBUG_LL
	{	/* Debug UART mapping */
		.virtual	= IXP4XX_DEBUG_UART_BASE_VIRT,
		.pfn		= __phys_to_pfn(IXP4XX_DEBUG_UART_BASE_PHYS),
		.length		= IXP4XX_DEBUG_UART_REGION_SIZE,
		.type		= MT_DEVICE
	}
#endif
};
