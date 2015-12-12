#ifdef USE_DMA_COHERENT_MEM_BLOCKS
if (dev->using_mem_coherent)
			dma_free_coherent(&dev->netdev->dev, dev->shared_data->num_pages_per_block * PAGE_SIZE,
					dev->shared_data->mem_blocks[dev->shared_data->num_mem_blocks - 1].kernel_addr,
					(dma_addr_t)dev->shared_data->mem_blocks[dev->shared_data->num_mem_blocks - 1].mem_handle);
		else
#endif
			kfree(dev->shared_data->mem_blocks[dev->shared_data->num_mem_blocks - 1].kernel_addr);
