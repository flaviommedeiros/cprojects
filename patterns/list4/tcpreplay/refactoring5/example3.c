#ifdef USE_DMA_COHERENT_MEM_BLOCKS
if (dev->using_mem_coherent)
		dma_free_coherent(&dev->netdev->dev, dev->shared_data->num_pages_per_block * PAGE_SIZE,
				mem_block_p, (dma_addr_t)entry->mem_handle);
	else
#endif
		kfree(mem_block_p);
