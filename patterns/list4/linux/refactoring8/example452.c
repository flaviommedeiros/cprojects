static struct tree_descr files[] = {
		{ "cache_threshold",
		  &sel_avc_cache_threshold_ops, S_IRUGO|S_IWUSR },
		{ "hash_stats", &sel_avc_hash_stats_ops, S_IRUGO },
#ifdef CONFIG_SECURITY_SELINUX_AVC_STATS
		{ "cache_stats", &sel_avc_cache_stats_ops, S_IRUGO },
#endif
	};
