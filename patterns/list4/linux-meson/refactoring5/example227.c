#ifdef CONFIG_ISA_DMA_API
if (devpriv->current_transfer == isa_dma_transfer) {
		/*
		 * if a dma terminal count of external stop trigger
		 * has occurred
		 */
		if (devpriv->stat1 & STAT1_GATA0 ||
		    (board->register_layout == labpc_1200_layout
		     && devpriv->stat2 & STAT2_OUTA1)) {
			handle_isa_dma(dev);
		}
	} else
#endif
		labpc_drain_fifo(dev);
