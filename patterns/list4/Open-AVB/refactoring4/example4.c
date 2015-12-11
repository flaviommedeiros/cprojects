#ifdef CONFIG_IGB_DISABLE_PACKET_SPLIT
if (!igb_alloc_mapped_skb(rx_ring, bi))
#else
		if (!igb_alloc_mapped_page(rx_ring, bi))
#endif /* CONFIG_IGB_DISABLE_PACKET_SPLIT */
			break;
