#ifdef CONFIG_STMMAC_TIMER
if (likely(priv->tm->enable))
		priv->tm->timer_stop();
	else
#endif
		priv->hw->dma->disable_dma_irq(priv->ioaddr);
