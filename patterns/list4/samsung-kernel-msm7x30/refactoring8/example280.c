static struct addr_marker address_markers[] = {
	{ 0, "User Space" },
#ifdef CONFIG_X86_64
	{ 0x8000000000000000UL, "Kernel Space" },
	{ PAGE_OFFSET,		"Low Kernel Mapping" },
	{ VMALLOC_START,        "vmalloc() Area" },
	{ VMEMMAP_START,        "Vmemmap" },
	{ ESPFIX_BASE_ADDR,	"ESPfix Area", 16 },
	{ __START_KERNEL_map,   "High Kernel Mapping" },
	{ MODULES_VADDR,        "Modules" },
	{ MODULES_END,          "End Modules" },
#else
	{ PAGE_OFFSET,          "Kernel Mapping" },
	{ 0/* VMALLOC_START */, "vmalloc() Area" },
	{ 0/*VMALLOC_END*/,     "vmalloc() End" },
# ifdef CONFIG_HIGHMEM
	{ 0/*PKMAP_BASE*/,      "Persisent kmap() Area" },
# endif
	{ 0/*FIXADDR_START*/,   "Fixmap Area" },
#endif
	{ -1, NULL }		/* End of list */
};
