#ifdef CONFIG_HIGHMEM
if (PageHighMem(sg->page)) {
			dma_sync_high(sg, direction);
			sg->dma_address = (page_to_pfn(sg->page) << PAGE_SHIFT) + sg->offset;
		}
		else
#endif
		{
			addr = (unsigned long) page_address(sg->page);
			if (!plat_device_is_coherent(dev) && addr)
				__dma_sync(addr + sg->offset, sg->length, direction);
			sg->dma_address = plat_map_dma_mem(dev,
					                   (void *)(addr + sg->offset),
							   sg->length);
		}
