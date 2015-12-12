static struct attribute *hugepage_attr[] = {
	&enabled_attr.attr,
	&defrag_attr.attr,
#ifdef CONFIG_DEBUG_VM
	&debug_cow_attr.attr,
#endif
	NULL,
};
