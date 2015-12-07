#ifndef CONFIG_SMP
if (mapping && !mapping_mapped(mapping))
		set_bit(PG_dcache_dirty, &page->flags);
	else
#endif
	{
		__flush_dcache_page(mapping, page);
		if (mapping && cache_is_vivt())
			__flush_dcache_aliases(mapping, page);
	}
