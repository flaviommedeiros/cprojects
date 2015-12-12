static struct attribute *selfballoon_attrs[] = {
	&dev_attr_selfballooning.attr,
	&dev_attr_selfballoon_interval.attr,
	&dev_attr_selfballoon_downhysteresis.attr,
	&dev_attr_selfballoon_uphysteresis.attr,
	&dev_attr_selfballoon_min_usable_mb.attr,
#ifdef CONFIG_FRONTSWAP
	&dev_attr_frontswap_selfshrinking.attr,
	&dev_attr_frontswap_hysteresis.attr,
	&dev_attr_frontswap_inertia.attr,
#endif
	NULL
};
