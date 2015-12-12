#ifdef SMC_USE_DMA
if (!lp->txdma_active)
#endif
				netif_wake_queue(dev);
