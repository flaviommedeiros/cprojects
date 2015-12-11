switch (adapter->hw.mac.type) {
#ifdef HAVE_PTP_1588_CLOCK
	case e1000_82575:
		info->so_timestamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		return 0;
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
		info->so_timestamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE |
			SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE;

		if (adapter->ptp_clock)
			info->phc_index = ptp_clock_index(adapter->ptp_clock);
		else
			info->phc_index = -1;

		info->tx_types =
			(1 << HWTSTAMP_TX_OFF) |
			(1 << HWTSTAMP_TX_ON);

		info->rx_filters = 1 << HWTSTAMP_FILTER_NONE;

		/* 82576 does not support timestamping all packets. */
		if (adapter->hw.mac.type >= e1000_82580)
			info->rx_filters |= 1 << HWTSTAMP_FILTER_ALL;
		else
			info->rx_filters |=
				(1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
				(1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
				(1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
				(1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
				(1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
				(1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
				(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);

		return 0;
#endif /* HAVE_PTP_1588_CLOCK */
	default:
		return -EOPNOTSUPP;
	}
