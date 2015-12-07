#ifdef CONFIG_HIGHMEM
if (PageHighMem(sg->page)) {
				dma_sync_high(sg, direction);
			}
			else
#endif
			{
				addr = (unsigned long) page_address(sg->page);
				if (addr)
					__dma_sync(addr + sg->offset, sg->length,
					           direction);
			}
