static struct of_device_id vexpress_hwmon_of_match[] = {
#if !defined(CONFIG_REGULATOR_VEXPRESS)
	{
		.compatible = "arm,vexpress-volt",
		.data = &vexpress_hwmon_group_volt,
	},
#endif
	{
		.compatible = "arm,vexpress-amp",
		.data = &vexpress_hwmon_group_amp,
	}, {
		.compatible = "arm,vexpress-temp",
		.data = &vexpress_hwmon_group_temp,
	}, {
		.compatible = "arm,vexpress-power",
		.data = &vexpress_hwmon_group_power,
	}, {
		.compatible = "arm,vexpress-energy",
		.data = &vexpress_hwmon_group_energy,
	},
	{}
};
