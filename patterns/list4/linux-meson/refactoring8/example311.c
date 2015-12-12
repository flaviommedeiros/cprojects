static struct addr_marker address_markers[] = {
	[IDENTITY_NR]	  = {0, "Identity Mapping"},
	[KERNEL_START_NR] = {(unsigned long)&_stext, "Kernel Image Start"},
	[KERNEL_END_NR]	  = {(unsigned long)&_end, "Kernel Image End"},
	[VMEMMAP_NR]	  = {0, "vmemmap Area"},
	[VMALLOC_NR]	  = {0, "vmalloc Area"},
#ifdef CONFIG_64BIT
	[MODULES_NR]	  = {0, "Modules Area"},
#endif
	{ -1, NULL }
};
