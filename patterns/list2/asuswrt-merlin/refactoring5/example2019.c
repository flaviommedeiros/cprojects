#ifdef ENABLE_DMA
if ( lp->use_dma ) {
				/* Check for DMA Rx packets */
				if ( lp->hcfCtx.IFB_DmaPackets & HREG_EV_RDMAD ) {
					wl_rx_dma( dev );
					stop = FALSE;
				}
				/* Return Tx DMA descriptors to host */
				if ( lp->hcfCtx.IFB_DmaPackets & HREG_EV_TDMAD ) {
					wl_pci_dma_hcf_reclaim_tx( lp );
					stop = FALSE;
				}
			}
			else
#endif // ENABLE_DMA
			{
				/* Check for Rx packets */
				if ( lp->hcfCtx.IFB_RxLen != 0 ) {
					wl_rx( dev );
					stop = FALSE;
				}
				/* Make sure that queued frames get sent */
				if ( wl_send( lp )) {
					stop = FALSE;
				}
			}
