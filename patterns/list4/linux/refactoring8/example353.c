unsigned long zones_size[MAX_NR_ZONES] = {
		[ZONE_DMA] = max_low_pfn - ARCH_PFN_OFFSET,
#ifdef CONFIG_HIGHMEM
		[ZONE_HIGHMEM] = max_pfn - max_low_pfn,
#endif
	};
