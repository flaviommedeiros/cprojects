static struct attribute *st_drv_attrs[] = {
	&driver_attr_try_direct_io.attr,
	&driver_attr_fixed_buffer_size.attr,
	&driver_attr_max_sg_segs.attr,
	&driver_attr_version.attr,
#if DEBUG
	&driver_attr_debug_flag.attr,
#endif
	NULL,
};
