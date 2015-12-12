#ifdef CONFIG_STMMAC_TIMER
if (likely(priv->tm->enable))
		priv->tm->timer_start(tmrate);
	else
#endif
		priv->hw->dma->enable_dma_irq(priv->ioaddr);
