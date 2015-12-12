unsigned long zones_size[MAX_NR_ZONES] = {
		[0] = 0,
		[ZONE_DMA] = (end_mem - PAGE_OFFSET) >> PAGE_SHIFT,
		[ZONE_NORMAL] = 0,
#ifdef CONFIG_HIGHMEM
		[ZONE_HIGHMEM] = 0,
#endif
	};
