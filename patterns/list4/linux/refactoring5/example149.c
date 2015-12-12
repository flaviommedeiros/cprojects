#ifdef CONFIG_MIPS_ELF_APPENDED_DTB
if (!fdt_check_header(&__appended_dtb)) {
		fdt = &__appended_dtb;
		do_prune = false;
		pr_info("Using appended Device Tree.\n");
	} else
#endif
	if (octeon_bootinfo->minor_version >= 3 && octeon_bootinfo->fdt_addr) {
		fdt = phys_to_virt(octeon_bootinfo->fdt_addr);
		if (fdt_check_header(fdt))
			panic("Corrupt Device Tree passed to kernel.");
		do_prune = false;
		pr_info("Using passed Device Tree.\n");
	} else if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
		fdt = &__dtb_octeon_68xx_begin;
		do_prune = true;
	} else {
		fdt = &__dtb_octeon_3xxx_begin;
		do_prune = true;
	}
