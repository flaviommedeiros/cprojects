static struct map_desc io_desc[] __initdata = {
	{
		.virtual	= TTC0_VIRT,
		.pfn		= __phys_to_pfn(TTC0_PHYS),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= SCU_PERIPH_VIRT,
		.pfn		= __phys_to_pfn(SCU_PERIPH_PHYS),
		.length		= SZ_8K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= PL310_L2CC_VIRT,
		.pfn		= __phys_to_pfn(PL310_L2CC_PHYS),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},

#ifdef CONFIG_DEBUG_LL
	{
		.virtual	= UART0_VIRT,
		.pfn		= __phys_to_pfn(UART0_PHYS),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
#endif

};
