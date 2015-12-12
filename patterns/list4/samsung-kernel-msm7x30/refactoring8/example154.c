static struct attribute *lightsensor_attributes[] = {
	&dev_attr_delay.attr,
	&dev_attr_enable.attr,
	&dev_attr_wake.attr,
	&dev_attr_raw_data.attr,
	&dev_attr_status.attr,
	&dev_attr_autobrightness.attr,
#ifdef SENSOR_ENABLE_TESTMODE_ABS_Y
	&dev_attr_testmode.attr,
#endif
	&dev_attr_lightsensor_file_state.attr,
	NULL
};
