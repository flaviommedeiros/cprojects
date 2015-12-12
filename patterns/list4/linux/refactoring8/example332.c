static struct map_desc ebsa285_host_io_desc[] __initdata = {
#if defined(CONFIG_ARCH_FOOTBRIDGE) && defined(CONFIG_FOOTBRIDGE_HOST)
	{
		.virtual	= PCIMEM_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_MEM),
		.length		= PCIMEM_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= PCICFG0_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_TYPE_0_CONFIG),
		.length		= PCICFG0_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= PCICFG1_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_TYPE_1_CONFIG),
		.length		= PCICFG1_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= PCIIACK_BASE,
		.pfn		= __phys_to_pfn(DC21285_PCI_IACK),
		.length		= PCIIACK_SIZE,
		.type		= MT_DEVICE,
	},
#endif
};
