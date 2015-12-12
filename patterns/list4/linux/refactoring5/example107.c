#ifdef CONFIG_PPC_FSL_BOOK3E
if (mmu_has_feature(MMU_FTR_TYPE_FSL_E)) {
		unsigned long linear_sz;
		unsigned int num_cams;

		/* use a quarter of the TLBCAM for bolted linear map */
		num_cams = (mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY) / 4;

		linear_sz = map_mem_in_cams(first_memblock_size, num_cams,
					    true);

		ppc64_rma_size = min_t(u64, linear_sz, 0x40000000);
	} else
#endif
		ppc64_rma_size = min_t(u64, first_memblock_size, 0x40000000);
