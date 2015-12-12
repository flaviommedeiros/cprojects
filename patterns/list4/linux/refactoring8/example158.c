static struct attribute*
ds1685_rtc_sysfs_ctrl4a_attrs[] = {
	&dev_attr_vrt2.attr,
	&dev_attr_incr.attr,
	&dev_attr_pab.attr,
	&dev_attr_rf.attr,
	&dev_attr_wf.attr,
	&dev_attr_kf.attr,
#if !defined(CONFIG_RTC_DRV_DS1685) && !defined(CONFIG_RTC_DRV_DS1689)
	&dev_attr_bme.attr,
#endif
	NULL,
};
