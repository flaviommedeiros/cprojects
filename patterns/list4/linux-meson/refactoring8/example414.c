static struct map_desc r8a7740_io_desc[] __initdata = {
	 /*
	  * for CPGA/INTC/PFC
	  * 0xe6000000-0xefffffff -> 0xe6000000-0xefffffff
	  */
	{
		.virtual	= 0xe6000000,
		.pfn		= __phys_to_pfn(0xe6000000),
		.length		= 160 << 20,
		.type		= MT_DEVICE_NONSHARED
	},
#ifdef CONFIG_CACHE_L2X0
	/*
	 * for l2x0_init()
	 * 0xf0100000-0xf0101000 -> 0xf0002000-0xf0003000
	 */
	{
		.virtual	= 0xf0002000,
		.pfn		= __phys_to_pfn(0xf0100000),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE_NONSHARED
	},
#endif
};
