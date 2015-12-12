static struct attribute *default_attrs[] = {
	&total_trans.attr,
	&time_in_state.attr,
#ifdef CONFIG_CPU_FREQ_STAT_DETAILS
	&trans_table.attr,
#endif
	NULL
};
