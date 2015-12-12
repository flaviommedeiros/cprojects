static const struct of_device_id vexpress_hwmon_of_match[] = {
#if !defined(CONFIG_REGULATOR_VEXPRESS)
	{
		.compatible = "arm,vexpress-volt",
		.data = &vexpress_hwmon_volt,
	},
#endif
	{
		.compatible = "arm,vexpress-amp",
		.data = &vexpress_hwmon_amp,
	}, {
		.compatible = "arm,vexpress-temp",
		.data = &vexpress_hwmon_temp,
	}, {
		.compatible = "arm,vexpress-power",
		.data = &vexpress_hwmon_power,
	}, {
		.compatible = "arm,vexpress-energy",
		.data = &vexpress_hwmon_energy,
	},
	{}
};
