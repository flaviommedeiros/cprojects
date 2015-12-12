#ifdef IXGBE_FCOE
if (tx_flags & (IXGBE_TX_FLAGS_TXSW | IXGBE_TX_FLAGS_FCOE))
#else
	if (tx_flags & IXGBE_TX_FLAGS_TXSW)
#endif
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_CC);
