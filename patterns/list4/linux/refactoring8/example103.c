static const struct ixgbe_stats ixgbe_gstrings_stats[] = {
	{"rx_packets", IXGBEVF_STAT(stats.vfgprc, stats.base_vfgprc,
				    stats.saved_reset_vfgprc)},
	{"tx_packets", IXGBEVF_STAT(stats.vfgptc, stats.base_vfgptc,
				    stats.saved_reset_vfgptc)},
	{"rx_bytes", IXGBEVF_STAT(stats.vfgorc, stats.base_vfgorc,
				  stats.saved_reset_vfgorc)},
	{"tx_bytes", IXGBEVF_STAT(stats.vfgotc, stats.base_vfgotc,
				  stats.saved_reset_vfgotc)},
	{"tx_busy", IXGBEVF_ZSTAT(tx_busy)},
	{"tx_restart_queue", IXGBEVF_ZSTAT(restart_queue)},
	{"tx_timeout_count", IXGBEVF_ZSTAT(tx_timeout_count)},
	{"multicast", IXGBEVF_STAT(stats.vfmprc, stats.base_vfmprc,
				   stats.saved_reset_vfmprc)},
	{"rx_csum_offload_errors", IXGBEVF_ZSTAT(hw_csum_rx_error)},
#ifdef BP_EXTENDED_STATS
	{"rx_bp_poll_yield", IXGBEVF_ZSTAT(bp_rx_yields)},
	{"rx_bp_cleaned", IXGBEVF_ZSTAT(bp_rx_cleaned)},
	{"rx_bp_misses", IXGBEVF_ZSTAT(bp_rx_missed)},
	{"tx_bp_napi_yield", IXGBEVF_ZSTAT(bp_tx_yields)},
	{"tx_bp_cleaned", IXGBEVF_ZSTAT(bp_tx_cleaned)},
	{"tx_bp_misses", IXGBEVF_ZSTAT(bp_tx_missed)},
#endif
};
