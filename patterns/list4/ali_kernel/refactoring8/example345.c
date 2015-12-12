struct toa_stats_entry toa_stats[] = {
	TOA_STAT_ITEM("syn_recv_sock_toa", SYN_RECV_SOCK_TOA_CNT),
	TOA_STAT_ITEM("syn_recv_sock_no_toa", SYN_RECV_SOCK_NO_TOA_CNT),
	TOA_STAT_ITEM("getname_toa_ok_v4", GETNAME_TOA_OK_CNT_V4),
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	TOA_STAT_ITEM("getname_toa_ok_v6", GETNAME_TOA_OK_CNT_V6),
	TOA_STAT_ITEM("getname_toa_ok_mapped", GETNAME_TOA_OK_CNT_MAPPED),
#endif
	TOA_STAT_ITEM("getname_toa_mismatch", GETNAME_TOA_MISMATCH_CNT),
	TOA_STAT_ITEM("getname_toa_bypass", GETNAME_TOA_BYPASS_CNT),
	TOA_STAT_ITEM("getname_toa_empty", GETNAME_TOA_EMPTY_CNT),
	TOA_STAT_END
};
