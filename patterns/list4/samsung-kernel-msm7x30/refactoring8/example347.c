static struct slim_boardinfo msm_slim_devices[] = {
	/* add slimbus slaves as needed */
#ifdef CONFIG_WCD9310_CODEC
	{
		.bus_num = 1,
		.slim_slave = &msm_slim_tabla20,
	},
#endif
};
