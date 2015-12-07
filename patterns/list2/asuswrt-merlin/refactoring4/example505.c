#ifdef CONFIG_X86_PAE
if (pgd_index(cpu->lg->kernel_address) == SWITCHER_PGD_INDEX &&
		pmd_index(cpu->lg->kernel_address) == SWITCHER_PMD_INDEX)
#else
	if (pgd_index(cpu->lg->kernel_address) >= SWITCHER_PGD_INDEX)
#endif
		kill_guest(cpu, "bad kernel address %#lx",
				 cpu->lg->kernel_address);
