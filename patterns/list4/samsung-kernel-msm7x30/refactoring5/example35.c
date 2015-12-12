#ifdef BCM_CNIC
if (!bp->rx_ring_size && IS_MF_STORAGE_SD(bp)) {
		rx_ring_size = MIN_RX_SIZE_NONTPA;
		bp->rx_ring_size = rx_ring_size;
	} else
#endif
	if (!bp->rx_ring_size) {
		u32 cfg = SHMEM_RD(bp,
			     dev_info.port_hw_config[BP_PORT(bp)].default_cfg);

		rx_ring_size = MAX_RX_AVAIL/BNX2X_NUM_RX_QUEUES(bp);

		/* Dercease ring size for 1G functions */
		if ((cfg & PORT_HW_CFG_NET_SERDES_IF_MASK) ==
		    PORT_HW_CFG_NET_SERDES_IF_SGMII)
			rx_ring_size /= 10;

		/* allocate at least number of buffers required by FW */
		rx_ring_size = max_t(int, bp->disable_tpa ? MIN_RX_SIZE_NONTPA :
				     MIN_RX_SIZE_TPA, rx_ring_size);

		bp->rx_ring_size = rx_ring_size;
	} else /* if rx_ring_size specified - use it */
		rx_ring_size = bp->rx_ring_size;
