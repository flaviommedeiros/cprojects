return (memType == DMA_MEM_TYPE_DMA)
#if ALLOW_MAP_OF_KMALLOC_MEMORY
	    || (memType == DMA_MEM_TYPE_KMALLOC)
#endif
	    || (memType == DMA_MEM_TYPE_USER);
