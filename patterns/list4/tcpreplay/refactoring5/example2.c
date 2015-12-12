#ifdef USE_DMA_COHERENT_MEM_BLOCKS
if (dev->using_mem_coherent)
		mem_block_p = dma_alloc_coherent(dev->netdev->dev.parent, dev->shared_data->num_pages_per_block * PAGE_SIZE,
				(dma_addr_t*)&entry->mem_handle, GFP_KERNEL);
	else
#endif
		mem_block_p = kmalloc(dev->shared_data->num_pages_per_block * PAGE_SIZE, GFP_KERNEL);
