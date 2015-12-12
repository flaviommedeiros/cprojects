static struct ctl_table irda_table[] = {
	{
		.procname	= "discovery",
		.data		= &sysctl_discovery,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= do_discovery,
	},
	{
		.procname	= "devname",
		.data		= sysctl_devname,
		.maxlen		= 65,
		.mode		= 0644,
		.proc_handler	= do_devname,
	},
#ifdef CONFIG_IRDA_FAST_RR
	{
		.procname	= "fast_poll_increase",
		.data		= &sysctl_fast_poll_increase,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec
	},
#endif
	{
		.procname	= "discovery_slots",
		.data		= &sysctl_discovery_slots,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_discovery_slots,
		.extra2		= &max_discovery_slots
	},
	{
		.procname	= "discovery_timeout",
		.data		= &sysctl_discovery_timeout,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec
	},
	{
		.procname	= "slot_timeout",
		.data		= &sysctl_slot_timeout,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_slot_timeout,
		.extra2		= &max_slot_timeout
	},
	{
		.procname	= "max_baud_rate",
		.data		= &sysctl_max_baud_rate,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_max_baud_rate,
		.extra2		= &max_max_baud_rate
	},
	{
		.procname	= "min_tx_turn_time",
		.data		= &sysctl_min_tx_turn_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_min_tx_turn_time,
		.extra2		= &max_min_tx_turn_time
	},
	{
		.procname	= "max_tx_data_size",
		.data		= &sysctl_max_tx_data_size,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_max_tx_data_size,
		.extra2		= &max_max_tx_data_size
	},
	{
		.procname	= "max_tx_window",
		.data		= &sysctl_max_tx_window,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_max_tx_window,
		.extra2		= &max_max_tx_window
	},
	{
		.procname	= "max_noreply_time",
		.data		= &sysctl_max_noreply_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_max_noreply_time,
		.extra2		= &max_max_noreply_time
	},
	{
		.procname	= "warn_noreply_time",
		.data		= &sysctl_warn_noreply_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_warn_noreply_time,
		.extra2		= &max_warn_noreply_time
	},
	{
		.procname	= "lap_keepalive_time",
		.data		= &sysctl_lap_keepalive_time,
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_lap_keepalive_time,
		.extra2		= &max_lap_keepalive_time
	},
	{ }
};
