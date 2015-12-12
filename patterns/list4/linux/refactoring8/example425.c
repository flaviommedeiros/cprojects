static struct attribute *rx_queue_default_attrs[] = {
#ifdef CONFIG_RPS
	&rps_cpus_attribute.attr,
	&rps_dev_flow_table_cnt_attribute.attr,
#endif
	NULL
};
