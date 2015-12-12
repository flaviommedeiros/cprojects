return request_irq(get_dmte_irq(chan->chan), dma_tei,
#if defined(CONFIG_SH_DMA_IRQ_MULTI)
				IRQF_SHARED,
#else
				IRQF_DISABLED,
#endif
				chan->dev_id, chan);
