return bitmap_iterator_count(&it) +
			(priv->tx_ring_num * 2) +
#ifdef CONFIG_NET_RX_BUSY_POLL
			(priv->rx_ring_num * 5);
