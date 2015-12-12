static struct attribute *cpu_common_attrs[] = {
#ifdef CONFIG_HOTPLUG_CPU
	&dev_attr_configure.attr,
#endif
	&dev_attr_address.attr,
	NULL,
};
