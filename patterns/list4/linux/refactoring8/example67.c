static struct tree_descr xenfs_init_files[] = {
		[2] = { "xenbus", &xen_xenbus_fops, S_IRUSR|S_IWUSR },
		{ "capabilities", &capabilities_file_ops, S_IRUGO },
		{ "privcmd", &xen_privcmd_fops, S_IRUSR|S_IWUSR },
		{ "xsd_kva", &xsd_kva_file_ops, S_IRUSR|S_IWUSR},
		{ "xsd_port", &xsd_port_file_ops, S_IRUSR|S_IWUSR},
#ifdef CONFIG_XEN_SYMS
		{ "xensyms", &xensyms_ops, S_IRUSR},
#endif
		{""},
	};
