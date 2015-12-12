static struct attribute *il3945_sysfs_entries[] = {
	&dev_attr_antenna.attr,
	&dev_attr_channels.attr,
	&dev_attr_dump_errors.attr,
	&dev_attr_flags.attr,
	&dev_attr_filter_flags.attr,
	&dev_attr_measurement.attr,
	&dev_attr_retry_rate.attr,
	&dev_attr_status.attr,
	&dev_attr_temperature.attr,
	&dev_attr_tx_power.attr,
#ifdef CONFIG_IWLEGACY_DEBUG
	&dev_attr_debug_level.attr,
#endif
	NULL
};
