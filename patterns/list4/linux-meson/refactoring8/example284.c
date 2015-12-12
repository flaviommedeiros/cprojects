static struct attribute *pm_qos_latency_attrs[] = {
#ifdef CONFIG_PM_RUNTIME
	&dev_attr_pm_qos_resume_latency_us.attr,
#endif /* CONFIG_PM_RUNTIME */
	NULL,
};
