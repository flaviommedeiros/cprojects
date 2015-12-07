if (!image->arch.pgd ||
#ifdef CONFIG_X86_PAE
	    !image->arch.pmd0 || !image->arch.pmd1 ||
#endif
	    !image->arch.pte0 || !image->arch.pte1) {
		machine_kexec_free_page_tables(image);
		return -ENOMEM;
	}
