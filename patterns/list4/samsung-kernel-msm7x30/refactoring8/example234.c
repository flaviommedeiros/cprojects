static struct attribute *node_state_attrs[] = {
	&node_state_attr[0].attr.attr,
	&node_state_attr[1].attr.attr,
	&node_state_attr[2].attr.attr,
	&node_state_attr[3].attr.attr,
#ifdef CONFIG_HIGHMEM
	&node_state_attr[4].attr.attr,
#endif
	NULL
};
