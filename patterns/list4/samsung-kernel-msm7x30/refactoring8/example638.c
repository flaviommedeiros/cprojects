static struct attribute *v9fs_attrs[] = {
#ifdef CONFIG_9P_FSCACHE
	&v9fs_attr_cache.attr,
#endif
	NULL,
};
