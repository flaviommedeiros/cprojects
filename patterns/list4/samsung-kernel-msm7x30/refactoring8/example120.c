static int ttm_alloc_new_pages(struct list_head *pages, gfp_t gfp_flags,
		int ttm_flags, enum ttm_caching_state cstate, unsigned count)
{
	struct page **caching_array;
	struct page *p;
	int r = 0;
	unsigned i, cpages;
	unsigned max_cpages = min(count,
			(unsigned)(PAGE_SIZE/sizeof(struct page *)));

	/* allocate array for page caching change */
	caching_array = kmalloc(max_cpages*sizeof(struct page *), GFP_KERNEL);

	if (!caching_array) {
		pr_err("Unable to allocate table for new pages\n");
		return -ENOMEM;
	}

	for (i = 0, cpages = 0; i < count; ++i) {
		p = alloc_page(gfp_flags);

		if (!p) {
			pr_err("Unable to get page %u\n", i);

			/* store already allocated pages in the pool after
			 * setting the caching state */
			if (cpages) {
				r = ttm_set_pages_caching(caching_array,
							  cstate, cpages);
				if (r)
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
			}
			r = -ENOMEM;
			goto out;
		}

#ifdef CONFIG_HIGHMEM
		/* gfp flags of highmem page should never be dma32 so we
		 * we should be fine in such case
		 */
		if (!PageHighMem(p))
#endif
		{
			caching_array[cpages++] = p;
			if (cpages == max_cpages) {

				r = ttm_set_pages_caching(caching_array,
						cstate, cpages);
				if (r) {
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
					goto out;
				}
				cpages = 0;
			}
		}

		list_add(&p->lru, pages);
	}

	if (cpages) {
		r = ttm_set_pages_caching(caching_array, cstate, cpages);
		if (r)
			ttm_handle_caching_state_failure(pages,
					ttm_flags, cstate,
					caching_array, cpages);
	}
out:
	kfree(caching_array);

	return r;
}
