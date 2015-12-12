static struct attribute *bch_cache_set_internal_files[] = {
	&sysfs_active_journal_entries,

	sysfs_time_stats_attribute_list(btree_gc, sec, ms)
	sysfs_time_stats_attribute_list(btree_split, sec, us)
	sysfs_time_stats_attribute_list(btree_sort, ms, us)
	sysfs_time_stats_attribute_list(btree_read, ms, us)
	sysfs_time_stats_attribute_list(try_harder, ms, us)

	&sysfs_btree_nodes,
	&sysfs_btree_used_percent,
	&sysfs_btree_cache_max_chain,

	&sysfs_bset_tree_stats,
	&sysfs_cache_read_races,
	&sysfs_writeback_keys_done,
	&sysfs_writeback_keys_failed,

	&sysfs_trigger_gc,
	&sysfs_prune_cache,
#ifdef CONFIG_BCACHE_DEBUG
	&sysfs_verify,
	&sysfs_key_merging_disabled,
#endif
	&sysfs_gc_always_rewrite,
	&sysfs_btree_shrinker_disabled,
	&sysfs_copy_gc_enabled,
	NULL
};
