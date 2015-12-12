#ifdef CONFIG_ISA_DMA_API
if (devpriv->current_transfer == isa_dma_transfer) {
		/*
		 * if a dma terminal count of external stop trigger
		 * has occurred
		 */
		if (devpriv->status1_bits & DMATC_BIT ||
		    (thisboard->register_layout == labpc_1200_layout
		     && devpriv->status2_bits & A1_TC_BIT)) {
			handle_isa_dma(dev);
		}
	} else
#endif
		labpc_drain_fifo(dev);
