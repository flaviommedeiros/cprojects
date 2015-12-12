#ifdef HAVE_NDO_SET_FEATURES
if (!(netdev_ring(ring)->features & NETIF_F_RXCSUM))
#else
	if (!test_bit(IGB_RING_FLAG_RX_CSUM, &ring->flags))
#endif
		return;
