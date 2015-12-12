#ifdef CONFIG_STMMAC_TIMER
if (likely(priv->tm->enable))
		priv->tm->timer_stop();
	else
#endif
	writel(0, priv->dev->base_addr + DMA_INTR_ENA);
