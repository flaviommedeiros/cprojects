static const char myri10ge_gstrings_slice_stats[][ETH_GSTRING_LEN] = {
	"----------- slice ---------",
	"tx_pkt_start", "tx_pkt_done", "tx_req", "tx_done",
	"rx_small_cnt", "rx_big_cnt",
	"wake_queue", "stop_queue", "tx_linearized",
#ifdef CONFIG_NET_RX_BUSY_POLL
	"rx_lock_napi_yield", "rx_lock_poll_yield", "rx_busy_poll_miss",
	"rx_busy_poll_cnt",
#endif
};
