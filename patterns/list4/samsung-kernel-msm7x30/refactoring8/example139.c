static struct attribute *dev_attrs[] = {
#ifdef CONFIG_MMC_PERF_PROFILING
	&dev_attr_perf.attr,
#endif
	NULL,
};
