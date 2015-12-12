static struct attribute *adp8860_bl_attributes[] = {
	&dev_attr_l3_dark_max.attr,
	&dev_attr_l3_dark_dim.attr,
	&dev_attr_l2_office_max.attr,
	&dev_attr_l2_office_dim.attr,
	&dev_attr_l1_daylight_max.attr,
	&dev_attr_l1_daylight_dim.attr,
#ifdef ADP8860_EXT_FEATURES
	&dev_attr_ambient_light_level.attr,
	&dev_attr_ambient_light_zone.attr,
#endif
	NULL
};
