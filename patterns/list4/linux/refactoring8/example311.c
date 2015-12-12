static struct section_perm ro_perms[] = {
	/* Make kernel code and rodata RX (set RO). */
	{
		.start  = (unsigned long)_stext,
		.end    = (unsigned long)__init_begin,
#ifdef CONFIG_ARM_LPAE
		.mask   = ~L_PMD_SECT_RDONLY,
		.prot   = L_PMD_SECT_RDONLY,
#else
		.mask   = ~(PMD_SECT_APX | PMD_SECT_AP_WRITE),
		.prot   = PMD_SECT_APX | PMD_SECT_AP_WRITE,
		.clear  = PMD_SECT_AP_WRITE,
#endif
	},
};
