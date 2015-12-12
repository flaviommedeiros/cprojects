static struct ctl_table fs_dqstats_table[] = {
	{
		.procname	= "lookups",
		.data		= &dqstats.stat[DQST_LOOKUPS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "drops",
		.data		= &dqstats.stat[DQST_DROPS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "reads",
		.data		= &dqstats.stat[DQST_READS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "writes",
		.data		= &dqstats.stat[DQST_WRITES],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "cache_hits",
		.data		= &dqstats.stat[DQST_CACHE_HITS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "allocated_dquots",
		.data		= &dqstats.stat[DQST_ALLOC_DQUOTS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "free_dquots",
		.data		= &dqstats.stat[DQST_FREE_DQUOTS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
	{
		.procname	= "syncs",
		.data		= &dqstats.stat[DQST_SYNCS],
		.maxlen		= sizeof(int),
		.mode		= 0444,
		.proc_handler	= do_proc_dqstats,
	},
#ifdef CONFIG_PRINT_QUOTA_WARNING
	{
		.procname	= "warnings",
		.data		= &flag_print_warnings,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec,
	},
#endif
	{ },
};
