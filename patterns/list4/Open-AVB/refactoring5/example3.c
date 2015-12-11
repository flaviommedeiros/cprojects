#ifdef DEBUG
if (test_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags) &&
	    !(adapter->disable_hw_reset && adapter->tx_hang_detected)) {
#else
	if (test_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags)) {
#endif
		struct e1000_hw *hw = &adapter->hw;

		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of time_stamp and movement of i */
		clear_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
		if (tx_buffer->next_to_watch &&
		    time_after(jiffies, tx_buffer->time_stamp +
			       (adapter->tx_timeout_factor * HZ))
		    && !(E1000_READ_REG(hw, E1000_STATUS) &
			 E1000_STATUS_TXOFF)) {

			/* detected Tx unit hang */
#ifdef DEBUG
			adapter->tx_hang_detected = TRUE;
			if (adapter->disable_hw_reset) {
				DPRINTK(DRV, WARNING,
					"Deactivating netdev watchdog timer\n");
				if (del_timer(&netdev_ring(tx_ring)->watchdog_timer))
					dev_put(netdev_ring(tx_ring));
#ifndef HAVE_NET_DEVICE_OPS
				netdev_ring(tx_ring)->tx_timeout = NULL;
#endif
			}
#endif /* DEBUG */
			dev_err(tx_ring->dev,
				"Detected Tx Unit Hang\n"
				"  Tx Queue             <%d>\n"
				"  TDH                  <%x>\n"
				"  TDT                  <%x>\n"
				"  next_to_use          <%x>\n"
				"  next_to_clean        <%x>\n"
				"buffer_info[next_to_clean]\n"
				"  time_stamp           <%lx>\n"
				"  next_to_watch        <%p>\n"
				"  jiffies              <%lx>\n"
				"  desc.status          <%x>\n",
				tx_ring->queue_index,
				E1000_READ_REG(hw, E1000_TDH(tx_ring->reg_idx)),
				readl(tx_ring->tail),
				tx_ring->next_to_use,
				tx_ring->next_to_clean,
				tx_buffer->time_stamp,
				tx_buffer->next_to_watch,
				jiffies,
				tx_buffer->next_to_watch->wb.status);
			if (netif_is_multiqueue(netdev_ring(tx_ring)))
				netif_stop_subqueue(netdev_ring(tx_ring),
						    ring_queue_index(tx_ring));
			else
				netif_stop_queue(netdev_ring(tx_ring));

			/* we are about to reset, no point in enabling stuff */
			return true;
		}
	}

#define TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	if (unlikely(total_packets &&
		     netif_carrier_ok(netdev_ring(tx_ring)) &&
		     igb_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD)) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (netif_is_multiqueue(netdev_ring(tx_ring))) {
			if (__netif_subqueue_stopped(netdev_ring(tx_ring),
						ring_queue_index(tx_ring)) &&
			    !(test_bit(__IGB_DOWN, &adapter->state))) {
				netif_wake_subqueue(netdev_ring(tx_ring),
						    ring_queue_index(tx_ring));
				tx_ring->tx_stats.restart_queue++;
			}
		} else {
			if (netif_queue_stopped(netdev_ring(tx_ring)) &&
			    !(test_bit(__IGB_DOWN, &adapter->state))) {
				netif_wake_queue(netdev_ring(tx_ring));
				tx_ring->tx_stats.restart_queue++;
			}
		}
	}

	return !!budget;
}
