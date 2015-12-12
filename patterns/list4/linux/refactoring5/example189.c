#ifdef CONFIG_NET_RX_BUSY_POLL
if (dev->netdev_ops->ndo_busy_poll)
		features |= NETIF_F_BUSY_POLL;
	else
#endif
		features &= ~NETIF_F_BUSY_POLL;
