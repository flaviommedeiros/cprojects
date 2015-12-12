static const struct ctl_table ax25_param_table[] = {
	{
		.procname	= "ip_default_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_ipdefmode,
		.extra2		= &max_ipdefmode
	},
	{
		.procname	= "ax25_default_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_axdefmode,
		.extra2		= &max_axdefmode
	},
	{
		.procname	= "backoff_type",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_backoff,
		.extra2		= &max_backoff
	},
	{
		.procname	= "connect_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_conmode,
		.extra2		= &max_conmode
	},
	{
		.procname	= "standard_window_size",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_window,
		.extra2		= &max_window
	},
	{
		.procname	= "extended_window_size",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_ewindow,
		.extra2		= &max_ewindow
	},
	{
		.procname	= "t1_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_t1,
		.extra2		= &max_t1
	},
	{
		.procname	= "t2_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_t2,
		.extra2		= &max_t2
	},
	{
		.procname	= "t3_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_t3,
		.extra2		= &max_t3
	},
	{
		.procname	= "idle_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_idle,
		.extra2		= &max_idle
	},
	{
		.procname	= "maximum_retry_count",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_n2,
		.extra2		= &max_n2
	},
	{
		.procname	= "maximum_packet_length",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_paclen,
		.extra2		= &max_paclen
	},
	{
		.procname	= "protocol",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_proto,
		.extra2		= &max_proto
	},
#ifdef CONFIG_AX25_DAMA_SLAVE
	{
		.procname	= "dama_slave_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.extra1		= &min_ds_timeout,
		.extra2		= &max_ds_timeout
	},
#endif

	{ }	/* that's all, folks! */
};
