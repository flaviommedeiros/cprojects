#ifdef CONFIG_HAS_DMA
if (dma) {
			dev->coherent_dma_mask = ~0;
			txbuf = dmam_alloc_coherent(dev, txbuflen, &par->txbuf.dma, GFP_DMA);
		} else
#endif
		{
			txbuf = devm_kzalloc(par->info->device, txbuflen, GFP_KERNEL);
		}
