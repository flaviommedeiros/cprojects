#ifdef CONFIG_SWAP
if (unlikely(PageSwapCache(page))) {
		swp_entry_t entry;

		entry.val = page_private(page);
		mapping = swap_address_space(entry);
	} else
#endif
	if ((unsigned long)mapping & PAGE_MAPPING_ANON)
		mapping = NULL;
