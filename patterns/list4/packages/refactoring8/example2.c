static struct attribute *nct6775_attributes_other[] = {
	&dev_attr_cpu0_vid.attr,				/* 0 */
	&sensor_dev_attr_intrusion0_alarm.dev_attr.attr,	/* 1 */
	&sensor_dev_attr_intrusion1_alarm.dev_attr.attr,	/* 2 */
	&sensor_dev_attr_intrusion0_beep.dev_attr.attr,		/* 3 */
	&sensor_dev_attr_intrusion1_beep.dev_attr.attr,		/* 4 */
	&sensor_dev_attr_beep_enable.dev_attr.attr,		/* 5 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0)
	&dev_attr_name.attr,
#endif
	NULL
};
