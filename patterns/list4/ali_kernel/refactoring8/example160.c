static struct attribute *default_attrs[] = {
	&attr_physical_package_id.attr,
	&attr_core_id.attr,
	&attr_thread_siblings.attr,
	&attr_thread_siblings_list.attr,
	&attr_core_siblings.attr,
	&attr_core_siblings_list.attr,
#ifdef CONFIG_SCHED_BOOK
	&attr_book_id.attr,
	&attr_book_siblings.attr,
	&attr_book_siblings_list.attr,
#endif
	NULL
};
