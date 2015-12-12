#ifdef CONFIG_PPC_FSL_BOOK3E
if (mmu_has_feature(MMU_FTR_TYPE_FSL_E)) {
		unsigned long linear_sz;
		linear_sz = calc_cam_sz(first_memblock_size, PAGE_OFFSET,
					first_memblock_base);
		ppc64_rma_size = min_t(u64, linear_sz, 0x40000000);
	} else
#endif
		ppc64_rma_size = min_t(u64, first_memblock_size, 0x40000000);
