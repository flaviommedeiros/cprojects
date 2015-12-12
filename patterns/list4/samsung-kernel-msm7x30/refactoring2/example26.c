#ifdef CONFIG_HIGHMEM
if (!PageHighMem(p))
#endif
		{
			caching_array[cpages++] = p;
			if (cpages == max_cpages) {
				/* Note: Cannot hold the spinlock */
				r = ttm_set_pages_caching(pool, caching_array,
						 cpages);
				if (r) {
					ttm_dma_handle_caching_state_failure(
						pool, d_pages, caching_array,
						cpages);
					goto out;
				}
				cpages = 0;
			}
		}
