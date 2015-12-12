static struct attribute *default_attrs[] = {
	&_attr_total_trans.attr,
	&_attr_time_in_state.attr,
#ifdef CONFIG_CPU_FREQ_STAT_DETAILS
	&_attr_trans_table.attr,
#endif
	NULL
};
