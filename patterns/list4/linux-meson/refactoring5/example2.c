#ifdef CONFIG_INSTABOOT_MEM_MG
if (!istbt_pfn_touchable(pfn)) {
					if (forbidden_pages_map)
						memory_bm_clear_bit(forbidden_pages_map, pfn);

					if (free_pages_map)
						memory_bm_clear_bit(free_pages_map, pfn);

					istbt_pfn_destory(pfn);

				} else
#endif
				{

					if (swsusp_page_is_forbidden(page) &&
							swsusp_page_is_free(page)) {
						swsusp_unset_page_forbidden(page);
						swsusp_unset_page_free(page);
						__free_page(page);
					}
				}
