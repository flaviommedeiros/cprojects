if ((vf >= adapter->vfs_allocated_count) ||
		(!(E1000_READ_REG(hw, E1000_STATUS) & E1000_STATUS_LU)) ||
#ifdef HAVE_NDO_SET_VF_MIN_MAX_TX_RATE
		(max_tx_rate < 0) || (max_tx_rate > actual_link_speed))
#else
		(tx_rate < 0) || (tx_rate > actual_link_speed)
