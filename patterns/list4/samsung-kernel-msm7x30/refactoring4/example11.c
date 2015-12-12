#ifdef IXGBE_FCOE
if (tx_flags & (IXGBE_TX_FLAGS_TSO | IXGBE_TX_FLAGS_FSO))
#else
	if (tx_flags & IXGBE_TX_FLAGS_TSO)
#endif
		cmd_type |= cpu_to_le32(IXGBE_ADVTXD_DCMD_TSE);
