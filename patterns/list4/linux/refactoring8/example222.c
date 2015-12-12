static struct attribute *runtime_attrs[] = {
#ifndef CONFIG_PM_ADVANCED_DEBUG
	&dev_attr_runtime_status.attr,
#endif
	&dev_attr_control.attr,
	&dev_attr_runtime_suspended_time.attr,
	&dev_attr_runtime_active_time.attr,
	&dev_attr_autosuspend_delay_ms.attr,
	NULL,
};
