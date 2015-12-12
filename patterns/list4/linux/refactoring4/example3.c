#ifdef CONFIG_X86
if (!xen_pv_domain())
#else
	if (!xen_domain())
#endif
		return -ENODEV;
