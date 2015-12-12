unsigned long zones_size[MAX_NR_ZONES] = {
		[0] = 0,
		[ZONE_DMA] = (end_mem - CONFIG_PHY_RAM_BASE_ADDRESS) >> PAGE_SHIFT,
		[ZONE_NORMAL] = 0,
#ifdef CONFIG_HIGHMEM
		[ZONE_HIGHMEM] = 0,
#endif
	};
