static struct map_desc omap44xx_io_desc[] __initdata = {
	{
		.virtual	= L3_44XX_VIRT,
		.pfn		= __phys_to_pfn(L3_44XX_PHYS),
		.length		= L3_44XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_44XX_VIRT,
		.pfn		= __phys_to_pfn(L4_44XX_PHYS),
		.length		= L4_44XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= OMAP44XX_GPMC_VIRT,
		.pfn		= __phys_to_pfn(OMAP44XX_GPMC_PHYS),
		.length		= OMAP44XX_GPMC_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= OMAP44XX_EMIF1_VIRT,
		.pfn		= __phys_to_pfn(OMAP44XX_EMIF1_PHYS),
		.length		= OMAP44XX_EMIF1_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= OMAP44XX_EMIF2_VIRT,
		.pfn		= __phys_to_pfn(OMAP44XX_EMIF2_PHYS),
		.length		= OMAP44XX_EMIF2_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= OMAP44XX_DMM_VIRT,
		.pfn		= __phys_to_pfn(OMAP44XX_DMM_PHYS),
		.length		= OMAP44XX_DMM_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_PER_44XX_VIRT,
		.pfn		= __phys_to_pfn(L4_PER_44XX_PHYS),
		.length		= L4_PER_44XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.virtual	= L4_EMU_44XX_VIRT,
		.pfn		= __phys_to_pfn(L4_EMU_44XX_PHYS),
		.length		= L4_EMU_44XX_SIZE,
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
