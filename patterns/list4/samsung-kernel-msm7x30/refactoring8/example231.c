static struct attribute *wakeup_attrs[] = {
#ifdef CONFIG_PM_SLEEP
	&dev_attr_wakeup.attr,
	&dev_attr_wakeup_count.attr,
	&dev_attr_wakeup_active_count.attr,
	&dev_attr_wakeup_hit_count.attr,
	&dev_attr_wakeup_active.attr,
	&dev_attr_wakeup_total_time_ms.attr,
	&dev_attr_wakeup_max_time_ms.attr,
	&dev_attr_wakeup_last_time_ms.attr,
#endif
	NULL,
};
