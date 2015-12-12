static const struct attribute_group *part_attr_groups[] = {
	&part_attr_group,
#ifdef CONFIG_BLK_DEV_IO_TRACE
	&blk_trace_attr_group,
#endif
	NULL
};
