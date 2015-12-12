#ifdef IXGBE_FCOE
if (tx_flags & (IXGBE_TX_FLAGS_TSO | IXGBE_TX_FLAGS_FCOE))
#else
	if (tx_flags & IXGBE_TX_FLAGS_TSO)
#endif
		olinfo_status |= cpu_to_le32(1 << IXGBE_ADVTXD_IDX_SHIFT);
