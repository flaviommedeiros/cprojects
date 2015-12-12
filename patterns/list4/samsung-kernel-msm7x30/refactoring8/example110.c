static struct attribute *il_sysfs_entries[] = {
	&dev_attr_temperature.attr,
	&dev_attr_tx_power.attr,
#ifdef CONFIG_IWLEGACY_DEBUG
	&dev_attr_debug_level.attr,
#endif
	NULL
};
