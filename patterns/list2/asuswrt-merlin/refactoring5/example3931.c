#ifdef CONFIG_CPU_MICROMIPS
if ((unsigned long)tlb_do_page_fault_0 & 1) {
		uasm_i_lui(&p, K0, uasm_rel_hi((long)tlb_do_page_fault_0));
		uasm_i_addiu(&p, K0, K0, uasm_rel_lo((long)tlb_do_page_fault_0));
		uasm_i_jr(&p, K0);
	} else
#endif
		uasm_i_j(&p, (unsigned long)tlb_do_page_fault_0 & 0x0fffffff);
