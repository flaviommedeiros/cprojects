#ifdef CONFIG_NET_DMA
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
				tp->ucopy.dma_chan = net_dma_find_channel();
