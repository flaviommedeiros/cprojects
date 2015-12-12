#ifdef CONFIG_PPC_BOOK3E_MMU
if (mmu_has_feature(MMU_FTR_TYPE_3E)) {
		u32 mmucfg = mfspr(SPRN_MMUCFG);
		u32 pid_bits = (mmucfg & MMUCFG_PIDSIZE_MASK)
				>> MMUCFG_PIDSIZE_SHIFT;
		first_context = 1;
		last_context = (1UL << (pid_bits + 1)) - 1;
	} else
#endif
	{
		first_context = 1;
		last_context = 255;
	}
