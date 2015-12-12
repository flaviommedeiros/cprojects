struct ctl_table random_table[] = {
	{
		.procname	= "poolsize",
		.data		= &sysctl_poolsize,
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= proc_dointvec,
	},
	{
		.procname	= "entropy_avail",
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= proc_do_entropy,
		.data		= &input_pool.entropy_count,
	},
	{
		.procname	= "read_wakeup_threshold",
		.data		= &random_read_wakeup_bits,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_read_thresh,
		.extra2		= &max_read_thresh,
	},
	{
		.procname	= "write_wakeup_threshold",
		.data		= &random_write_wakeup_bits,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_write_thresh,
		.extra2		= &max_write_thresh,
	},
	{
		.procname	= "urandom_min_reseed_secs",
		.data		= &random_min_urandom_seed,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
	{
		.procname	= "boot_id",
		.data		= &sysctl_bootid,
		.maxlen		= 16,
		.mode		= 0444,
		.proc_handler	= proc_do_uuid,
	},
	{
		.procname	= "uuid",
		.maxlen		= 16,
		.mode		= 0444,
		.proc_handler	= proc_do_uuid,
	},
#ifdef ADD_INTERRUPT_BENCH
	{
		.procname	= "add_interrupt_avg_cycles",
		.data		= &avg_cycles,
		.maxlen		= sizeof(avg_cycles),
		.mode		= 0444,
		.proc_handler	= proc_doulongvec_minmax,
	},
	{
		.procname	= "add_interrupt_avg_deviation",
		.data		= &avg_deviation,
		.maxlen		= sizeof(avg_deviation),
		.mode		= 0444,
		.proc_handler	= proc_doulongvec_minmax,
	},
#endif
	{ }
};
