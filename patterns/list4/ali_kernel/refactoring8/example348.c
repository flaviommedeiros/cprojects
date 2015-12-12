static const ctl_table ax25_param_table[] = {
	{
		.ctl_name	= NET_AX25_IP_DEFAULT_MODE,
		.procname	= "ip_default_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_ipdefmode,
		.extra2		= &max_ipdefmode
	},
	{
		.ctl_name	= NET_AX25_DEFAULT_MODE,
		.procname	= "ax25_default_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_axdefmode,
		.extra2		= &max_axdefmode
	},
	{
		.ctl_name	= NET_AX25_BACKOFF_TYPE,
		.procname	= "backoff_type",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_backoff,
		.extra2		= &max_backoff
	},
	{
		.ctl_name	= NET_AX25_CONNECT_MODE,
		.procname	= "connect_mode",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_conmode,
		.extra2		= &max_conmode
	},
	{
		.ctl_name	= NET_AX25_STANDARD_WINDOW,
		.procname	= "standard_window_size",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_window,
		.extra2		= &max_window
	},
	{
		.ctl_name	= NET_AX25_EXTENDED_WINDOW,
		.procname	= "extended_window_size",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_ewindow,
		.extra2		= &max_ewindow
	},
	{
		.ctl_name	= NET_AX25_T1_TIMEOUT,
		.procname	= "t1_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_t1,
		.extra2		= &max_t1
	},
	{
		.ctl_name	= NET_AX25_T2_TIMEOUT,
		.procname	= "t2_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_t2,
		.extra2		= &max_t2
	},
	{
		.ctl_name	= NET_AX25_T3_TIMEOUT,
		.procname	= "t3_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_t3,
		.extra2		= &max_t3
	},
	{
		.ctl_name	= NET_AX25_IDLE_TIMEOUT,
		.procname	= "idle_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_idle,
		.extra2		= &max_idle
	},
	{
		.ctl_name	= NET_AX25_N2,
		.procname	= "maximum_retry_count",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_n2,
		.extra2		= &max_n2
	},
	{
		.ctl_name	= NET_AX25_PACLEN,
		.procname	= "maximum_packet_length",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_paclen,
		.extra2		= &max_paclen
	},
	{
		.ctl_name	= NET_AX25_PROTOCOL,
		.procname	= "protocol",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_proto,
		.extra2		= &max_proto
	},
#ifdef CONFIG_AX25_DAMA_SLAVE
	{
		.ctl_name	= NET_AX25_DAMA_SLAVE_TIMEOUT,
		.procname	= "dama_slave_timeout",
		.maxlen		= sizeof(int),
		.mode		= 0644,
		.proc_handler	= proc_dointvec_minmax,
		.strategy	= sysctl_intvec,
		.extra1		= &min_ds_timeout,
		.extra2		= &max_ds_timeout
	},
#endif

	{ .ctl_name = 0 }	/* that's all, folks! */
};
