#ifdef CONFIG_NET_DMA
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
				tp->ucopy.dma_chan = get_softnet_dma();
