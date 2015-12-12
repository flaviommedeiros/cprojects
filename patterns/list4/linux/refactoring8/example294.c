static struct ds_cap_state ds_states_template[] = {
	{
		.service_id	= "md-update",
		.data		= md_update_data,
	},
	{
		.service_id	= "domain-shutdown",
		.data		= domain_shutdown_data,
	},
	{
		.service_id	= "domain-panic",
		.data		= domain_panic_data,
	},
#ifdef CONFIG_HOTPLUG_CPU
	{
		.service_id	= "dr-cpu",
		.data		= dr_cpu_data,
	},
#endif
	{
		.service_id	= "pri",
		.data		= ds_pri_data,
	},
	{
		.service_id	= "var-config",
		.data		= ds_var_data,
	},
	{
		.service_id	= "var-config-backup",
		.data		= ds_var_data,
	},
};
