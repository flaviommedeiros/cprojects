static ctl_table arlan_conf_table3[] =
{

	ARLAN_SYSCTL_TABLE_TOTAL(3)

#ifdef ARLAN_PROC_SHM_DUMP
	{
		.ctl_name	= 150,
		.procname	= "arlan3-txRing",
		.data		= &arlan_drive_info,
		.maxlen		= ARLAN_STR_SIZE,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_infotxRing,
	},
	{
		.ctl_name	= 151,
		.procname	= "arlan3-rxRing",
		.data		= &arlan_drive_info,
		.maxlen		= ARLAN_STR_SIZE,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_inforxRing,
	},
	{
		.ctl_name	= 152,
		.procname	= "arlan3-18",
		.data		= &arlan_drive_info,
		.maxlen		= ARLAN_STR_SIZE,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_info18,
	},
	{
		.ctl_name	= 153,
		.procname	= "arlan3-ring",
		.data		= &arlan_drive_info,
		.maxlen		= ARLAN_STR_SIZE,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_info161719,
	},
	{
		.ctl_name	= 154,
		.procname	= "arlan3-shm-cpy",
		.data		= &arlan_drive_info,
		.maxlen		= ARLAN_STR_SIZE,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_info,
	},
#endif
	{
		.ctl_name	= 155,
		.procname	= "config3",
		.data		= &conf_reset_result,
		.maxlen		= 100,
		.mode		= 0400,
		.proc_handler	= &arlan_configure,
	},
	{
		.ctl_name	= 156,
		.procname	= "reset3",
		.data		= &conf_reset_result,
		.maxlen		= 100,
		.mode		= 0400,
		.proc_handler	= &arlan_sysctl_reset,
	},
	{ .ctl_name = 0 }
};
