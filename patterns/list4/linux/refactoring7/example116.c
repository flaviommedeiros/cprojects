return
#ifdef CONFIG_ZONE_DMA
		zone_page_state(&zones[ZONE_DMA], item) +
#endif
#ifdef CONFIG_ZONE_DMA32
		zone_page_state(&zones[ZONE_DMA32], item) +
#endif
#ifdef CONFIG_HIGHMEM
		zone_page_state(&zones[ZONE_HIGHMEM], item) +
#endif
		zone_page_state(&zones[ZONE_NORMAL], item) +
		zone_page_state(&zones[ZONE_MOVABLE], item);
