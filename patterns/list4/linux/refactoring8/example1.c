static struct cftype cfq_blkcg_legacy_files[] = {
	/* on root, weight is mapped to leaf_weight */
	{
		.name = "weight_device",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = cfqg_print_leaf_weight_device,
		.write = cfqg_set_leaf_weight_device,
	},
	{
		.name = "weight",
		.flags = CFTYPE_ONLY_ON_ROOT,
		.seq_show = cfq_print_leaf_weight,
		.write_u64 = cfq_set_leaf_weight,
	},

	/* no such mapping necessary for !roots */
	{
		.name = "weight_device",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cfqg_print_weight_device,
		.write = cfqg_set_weight_device,
	},
	{
		.name = "weight",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cfq_print_weight,
		.write_u64 = cfq_set_weight,
	},

	{
		.name = "leaf_weight_device",
		.seq_show = cfqg_print_leaf_weight_device,
		.write = cfqg_set_leaf_weight_device,
	},
	{
		.name = "leaf_weight",
		.seq_show = cfq_print_leaf_weight,
		.write_u64 = cfq_set_leaf_weight,
	},

	/* statistics, covers only the tasks in the cfqg */
	{
		.name = "time",
		.private = offsetof(struct cfq_group, stats.time),
		.seq_show = cfqg_print_stat,
	},
	{
		.name = "sectors",
		.seq_show = cfqg_print_stat_sectors,
	},
	{
		.name = "io_service_bytes",
		.private = (unsigned long)&blkcg_policy_cfq,
		.seq_show = blkg_print_stat_bytes,
	},
	{
		.name = "io_serviced",
		.private = (unsigned long)&blkcg_policy_cfq,
		.seq_show = blkg_print_stat_ios,
	},
	{
		.name = "io_service_time",
		.private = offsetof(struct cfq_group, stats.service_time),
		.seq_show = cfqg_print_rwstat,
	},
	{
		.name = "io_wait_time",
		.private = offsetof(struct cfq_group, stats.wait_time),
		.seq_show = cfqg_print_rwstat,
	},
	{
		.name = "io_merged",
		.private = offsetof(struct cfq_group, stats.merged),
		.seq_show = cfqg_print_rwstat,
	},
	{
		.name = "io_queued",
		.private = offsetof(struct cfq_group, stats.queued),
		.seq_show = cfqg_print_rwstat,
	},

	/* the same statictics which cover the cfqg and its descendants */
	{
		.name = "time_recursive",
		.private = offsetof(struct cfq_group, stats.time),
		.seq_show = cfqg_print_stat_recursive,
	},
	{
		.name = "sectors_recursive",
		.seq_show = cfqg_print_stat_sectors_recursive,
	},
	{
		.name = "io_service_bytes_recursive",
		.private = (unsigned long)&blkcg_policy_cfq,
		.seq_show = blkg_print_stat_bytes_recursive,
	},
	{
		.name = "io_serviced_recursive",
		.private = (unsigned long)&blkcg_policy_cfq,
		.seq_show = blkg_print_stat_ios_recursive,
	},
	{
		.name = "io_service_time_recursive",
		.private = offsetof(struct cfq_group, stats.service_time),
		.seq_show = cfqg_print_rwstat_recursive,
	},
	{
		.name = "io_wait_time_recursive",
		.private = offsetof(struct cfq_group, stats.wait_time),
		.seq_show = cfqg_print_rwstat_recursive,
	},
	{
		.name = "io_merged_recursive",
		.private = offsetof(struct cfq_group, stats.merged),
		.seq_show = cfqg_print_rwstat_recursive,
	},
	{
		.name = "io_queued_recursive",
		.private = offsetof(struct cfq_group, stats.queued),
		.seq_show = cfqg_print_rwstat_recursive,
	},
#ifdef CONFIG_DEBUG_BLK_CGROUP
	{
		.name = "avg_queue_size",
		.seq_show = cfqg_print_avg_queue_size,
	},
	{
		.name = "group_wait_time",
		.private = offsetof(struct cfq_group, stats.group_wait_time),
		.seq_show = cfqg_print_stat,
	},
	{
		.name = "idle_time",
		.private = offsetof(struct cfq_group, stats.idle_time),
		.seq_show = cfqg_print_stat,
	},
	{
		.name = "empty_time",
		.private = offsetof(struct cfq_group, stats.empty_time),
		.seq_show = cfqg_print_stat,
	},
	{
		.name = "dequeue",
		.private = offsetof(struct cfq_group, stats.dequeue),
		.seq_show = cfqg_print_stat,
	},
	{
		.name = "unaccounted_time",
		.private = offsetof(struct cfq_group, stats.unaccounted_time),
		.seq_show = cfqg_print_stat,
	},
#endif	/* CONFIG_DEBUG_BLK_CGROUP */
	{ }	/* terminate */
};
