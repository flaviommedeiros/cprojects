#ifdef CONFIG_SMP
if (sparc_cpu_model == sun4d) {
		BTFIXUPSET_CALL(flush_tlb_all, sun4dsmp_flush_tlb_all, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_mm, sun4dsmp_flush_tlb_mm, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_page, sun4dsmp_flush_tlb_page, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_range, sun4dsmp_flush_tlb_range, BTFIXUPCALL_NORM);
	} else
#endif
	{
		BTFIXUPSET_CALL(flush_tlb_all, viking_flush_tlb_all, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_mm, viking_flush_tlb_mm, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_page, viking_flush_tlb_page, BTFIXUPCALL_NORM);
		BTFIXUPSET_CALL(flush_tlb_range, viking_flush_tlb_range, BTFIXUPCALL_NORM);
	}
