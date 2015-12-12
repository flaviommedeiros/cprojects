static struct attribute *cpu_common_attrs[] = {
#ifdef CONFIG_HOTPLUG_CPU
	&attr_configure.attr,
#endif
	&attr_address.attr,
	&attr_polarization.attr,
	NULL,
};
