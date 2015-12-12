#ifdef CONFIG_HIGHMEM
if (page_address(page))
#endif
		__cpuc_flush_dcache_page(page_address(page));
