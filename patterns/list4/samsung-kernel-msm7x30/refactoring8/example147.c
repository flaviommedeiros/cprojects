static struct attribute *iwmct_sysfs_entries[] = {
	&dev_attr_cc_label_fw.attr,
#ifdef CONFIG_IWMC3200TOP_DEBUG
	&dev_attr_log_level.attr,
	&dev_attr_log_level_fw.attr,
#endif
	NULL
};
