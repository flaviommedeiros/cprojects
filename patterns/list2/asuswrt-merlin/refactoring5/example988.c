#ifdef CONFIG_ZONE_DMA
if (min_low_pfn < MAX_DMA_PFN && MAX_DMA_PFN <= max_low_pfn) {
		zones_size[ZONE_DMA] = MAX_DMA_PFN - min_low_pfn;
		zones_size[ZONE_NORMAL] = max_low_pfn - MAX_DMA_PFN;
	} else if (max_low_pfn < MAX_DMA_PFN)
		zones_size[ZONE_DMA] = max_low_pfn - min_low_pfn;
	else
#endif /* CONFIG_ZONE_DMA */
	zones_size[ZONE_NORMAL] = max_low_pfn - min_low_pfn;
