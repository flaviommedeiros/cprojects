static struct map_desc omap54xx_io_desc[] __initdata = {
	{
		.virtual	= L3_54XX_VIRT,
		.pfn		= __phys_to_pfn(L3_54XX_PHYS),
		.length		= L3_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_54XX_PHYS),
		.length		= L4_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_WK_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_WK_54XX_PHYS),
		.length		= L4_WK_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_PER_54XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER_54XX_PHYS),
		.length		= L4_PER_54XX_SIZE,
		.type		= MT_DEVICE,
	},
#ifdef CONFIG_OMAP4_ERRATA_I688
	{
		.virtual	= OMAP4_SRAM_VA,
		.pfn		= __phys_to_pfn(OMAP4_SRAM_PA),
		.length		= PAGE_SIZE,
		.type		= MT_MEMORY_SO,
	},
#endif
};
