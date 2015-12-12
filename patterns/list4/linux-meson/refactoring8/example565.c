static struct attribute *netdev_queue_default_attrs[] = {
	&queue_trans_timeout.attr,
#ifdef CONFIG_XPS
	&xps_cpus_attribute.attr,
#endif
	NULL
};
