static const struct attribute_group *common_cpu_attr_groups[] = {
#ifdef CONFIG_KEXEC
	&crash_note_cpu_attr_group,
#endif
	NULL
};