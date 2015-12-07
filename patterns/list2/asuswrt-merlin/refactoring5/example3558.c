#ifdef CONFIG_NET_DMA
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
				tp->ucopy.dma_chan = dma_find_channel(DMA_MEMCPY);
