#ifdef CONFIG_ZONE_DMA32
if (dev->coherent_dma_mask <= DMA_BIT_MASK(32))
		gfp |= __GFP_DMA32;
	else
#endif
		;
