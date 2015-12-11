#ifdef SKB_SHARED_TX_IS_UNION
if (unlikely(skb_tx(skb)->hardware)) {
#else
	if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)) {
#endif
		struct igb_adapter *adapter = netdev_priv(tx_ring->netdev);

		if (!test_and_set_bit_lock(__IGB_PTP_TX_IN_PROGRESS,
					   &adapter->state)) {
#ifdef SKB_SHARED_TX_IS_UNION
			skb_tx(skb)->in_progress = 1;
#else
			skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
#endif
			tx_flags |= IGB_TX_FLAGS_TSTAMP;

			adapter->ptp_tx_skb = skb_get(skb);
			adapter->ptp_tx_start = jiffies;
			if (adapter->hw.mac.type == e1000_82576)
				schedule_work(&adapter->ptp_tx_work);
		}
	}
#endif /* HAVE_PTP_1588_CLOCK */
	skb_tx_timestamp(skb);
	if (skb_vlan_tag_present(skb)) {
		tx_flags |= IGB_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) << IGB_TX_FLAGS_VLAN_SHIFT);
	}

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = protocol;

	tso = igb_tso(tx_ring, first, &hdr_len);
	if (tso < 0)
		goto out_drop;
	else if (!tso)
		igb_tx_csum(tx_ring, first);

	igb_tx_map(tx_ring, first, hdr_len);

#ifndef HAVE_TRANS_START_IN_QUEUE
	netdev_ring(tx_ring)->trans_start = jiffies;

#endif
	/* Make sure there is space in the ring for the next send. */
	igb_maybe_stop_tx(tx_ring, DESC_NEEDED);

	return NETDEV_TX_OK;

out_drop:
	igb_unmap_and_free_tx_resource(tx_ring, first);

	return NETDEV_TX_OK;
}
