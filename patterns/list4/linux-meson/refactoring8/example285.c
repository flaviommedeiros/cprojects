static struct attribute *pm_qos_flags_attrs[] = {
#ifdef CONFIG_PM_RUNTIME
	&dev_attr_pm_qos_no_power_off.attr,
	&dev_attr_pm_qos_remote_wakeup.attr,
#endif /* CONFIG_PM_RUNTIME */
	NULL,
};
