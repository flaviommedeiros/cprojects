#ifdef CONFIG_STMMAC_TIMER
if (likely(priv->tm->enable))
		priv->tm->timer_start(tmrate);
	else
#endif
	writel(DMA_INTR_DEFAULT_MASK, priv->dev->base_addr + DMA_INTR_ENA);
