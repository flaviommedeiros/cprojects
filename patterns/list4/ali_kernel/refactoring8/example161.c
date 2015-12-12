struct sysdev_class_attribute *node_state_attr[] = {
	&attr_possible,
	&attr_online,
	&attr_has_normal_memory,
#ifdef CONFIG_HIGHMEM
	&attr_has_high_memory,
#endif
	&attr_has_cpu,
};
