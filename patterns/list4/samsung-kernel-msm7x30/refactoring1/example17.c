if (bootTC) {
#endif /* CONFIG_MIPS_MT_SMTC */
		cpu_cache_init();
		tlb_init();
#ifdef CONFIG_MIPS_MT_SMTC
	} else if (!secondaryTC) {
		/*
		 * First TC in non-boot VPE must do subset of tlb_init()
		 * for MMU countrol registers.
		 */
		write_c0_pagemask(PM_DEFAULT_MASK);
		write_c0_wired(0);
	}
#endif
