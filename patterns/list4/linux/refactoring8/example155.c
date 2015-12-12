static struct attribute *bch_flash_dev_files[] = {
	&sysfs_unregister,
#if 0
	&sysfs_data_csum,
#endif
	&sysfs_label,
	&sysfs_size,
	NULL
};
