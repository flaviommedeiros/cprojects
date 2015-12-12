static struct attribute *ksm_attrs[] = {
	&sleep_millisecs_attr.attr,
	&pages_to_scan_attr.attr,
	&run_attr.attr,
	&pages_shared_attr.attr,
	&pages_sharing_attr.attr,
	&pages_unshared_attr.attr,
	&pages_volatile_attr.attr,
	&full_scans_attr.attr,
#ifdef CONFIG_NUMA
	&merge_across_nodes_attr.attr,
#endif
	NULL,
};
