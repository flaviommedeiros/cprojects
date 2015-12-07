#ifdef CONFIG_BCM47XX
if (!test_and_set_bit(PG_dcache_clean, &from->flags))
#else
	if (test_and_clear_bit(PG_dcache_dirty, &from->flags))
#endif /* CONFIG_BCM47XX */
		__flush_dcache_page(page_mapping(from), from);
