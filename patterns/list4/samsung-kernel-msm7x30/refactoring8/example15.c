static struct module_attribute *modinfo_attrs[] = {
	&module_uevent,
	&modinfo_version,
	&modinfo_srcversion,
	&modinfo_initstate,
	&modinfo_coresize,
	&modinfo_initsize,
	&modinfo_taint,
#ifdef CONFIG_MODULE_UNLOAD
	&modinfo_refcnt,
#endif
	NULL,
};
