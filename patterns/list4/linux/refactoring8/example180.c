static struct attribute *adp8870_bl_attributes[] = {
	&dev_attr_l5_dark_max.attr,
	&dev_attr_l5_dark_dim.attr,
	&dev_attr_l4_indoor_max.attr,
	&dev_attr_l4_indoor_dim.attr,
	&dev_attr_l3_office_max.attr,
	&dev_attr_l3_office_dim.attr,
	&dev_attr_l2_bright_max.attr,
	&dev_attr_l2_bright_dim.attr,
	&dev_attr_l1_daylight_max.attr,
	&dev_attr_l1_daylight_dim.attr,
#ifdef ADP8870_EXT_FEATURES
	&dev_attr_ambient_light_level.attr,
	&dev_attr_ambient_light_zone.attr,
#endif
	NULL
};
