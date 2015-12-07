#ifndef CONFIG_SMP
if (DOMAIN_IO == 0 &&
	    (((cpu_architecture() >= CPU_ARCH_ARMv6) && (get_cr() & CR_XP)) ||
	       cpu_is_xsc3()) && pfn >= 0x100000 &&
	       !((__pfn_to_phys(pfn) | size | addr) & ~SUPERSECTION_MASK)) {
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_supersections(addr, pfn, size, type);
	} else if (!((__pfn_to_phys(pfn) | size | addr) & ~PMD_MASK)) {
		area->flags |= VM_ARM_SECTION_MAPPING;
		err = remap_area_sections(addr, pfn, size, type);
	} else
#endif
		err = ioremap_page_range(addr, addr + size, __pfn_to_phys(pfn),
					 __pgprot(type->prot_pte));
