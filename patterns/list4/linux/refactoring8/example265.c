static struct ctl_table frv_table[] =
{
	{
		.procname 	= "cache-mode",
		.data		= NULL,
		.maxlen		= 0,
		.mode		= 0644,
		.proc_handler	= procctl_frv_cachemode,
	},
#ifdef CONFIG_MMU
	{
		.procname	= "pin-cxnr",
		.data		= NULL,
		.maxlen		= 0,
		.mode		= 0644,
		.proc_handler	= procctl_frv_pin_cxnr
	},
#endif
	{}
};
