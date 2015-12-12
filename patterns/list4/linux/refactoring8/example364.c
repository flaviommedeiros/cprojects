static struct addr_marker address_markers[] = {
	{ VMALLOC_START,	"vmalloc() Area" },
	{ VMALLOC_END,		"vmalloc() End" },
#ifdef CONFIG_SPARSEMEM_VMEMMAP
	{ 0,			"vmemmap start" },
	{ 0,			"vmemmap end" },
#endif
	{ FIXADDR_START,	"Fixmap start" },
	{ FIXADDR_TOP,		"Fixmap end" },
	{ PCI_IO_START,		"PCI I/O start" },
	{ PCI_IO_END,		"PCI I/O end" },
	{ MODULES_VADDR,	"Modules start" },
	{ MODULES_END,		"Modules end" },
	{ PAGE_OFFSET,		"Kernel Mapping" },
	{ -1,			NULL },
};
