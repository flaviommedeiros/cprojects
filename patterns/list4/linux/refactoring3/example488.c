switch (book3e_htw_mode) {
	case PPC_HTW_IBM:
		patch_exception(0x1c0, exc_data_tlb_miss_htw_book3e);
		patch_exception(0x1e0, exc_instruction_tlb_miss_htw_book3e);
		break;
#ifdef CONFIG_PPC_FSL_BOOK3E
	case PPC_HTW_E6500:
		extlb_level_exc = EX_TLB_SIZE;
		patch_exception(0x1c0, exc_data_tlb_miss_e6500_book3e);
		patch_exception(0x1e0, exc_instruction_tlb_miss_e6500_book3e);
		break;
#endif
	}
