static struct attribute *default_attrs[] = {
	&dev_attr_physical_package_id.attr,
	&dev_attr_core_id.attr,
	&dev_attr_thread_siblings.attr,
	&dev_attr_thread_siblings_list.attr,
	&dev_attr_core_siblings.attr,
	&dev_attr_core_siblings_list.attr,
#ifdef CONFIG_SCHED_BOOK
	&dev_attr_book_id.attr,
	&dev_attr_book_siblings.attr,
	&dev_attr_book_siblings_list.attr,
#endif
	NULL
};
