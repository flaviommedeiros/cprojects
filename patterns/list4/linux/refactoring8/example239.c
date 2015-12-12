int kvmppc_load_last_inst(struct kvm_vcpu *vcpu, enum instruction_type type,
			  u32 *instr)
{
	gva_t geaddr;
	hpa_t addr;
	hfn_t pfn;
	hva_t eaddr;
	u32 mas1, mas2, mas3;
	u64 mas7_mas3;
	struct page *page;
	unsigned int addr_space, psize_shift;
	bool pr;
	unsigned long flags;

	/* Search TLB for guest pc to get the real address */
	geaddr = kvmppc_get_pc(vcpu);

	addr_space = (vcpu->arch.shared->msr & MSR_IS) >> MSR_IR_LG;

	local_irq_save(flags);
	mtspr(SPRN_MAS6, (vcpu->arch.pid << MAS6_SPID_SHIFT) | addr_space);
	mtspr(SPRN_MAS5, MAS5_SGS | get_lpid(vcpu));
	asm volatile("tlbsx 0, %[geaddr]\n" : :
		     [geaddr] "r" (geaddr));
	mtspr(SPRN_MAS5, 0);
	mtspr(SPRN_MAS8, 0);
	mas1 = mfspr(SPRN_MAS1);
	mas2 = mfspr(SPRN_MAS2);
	mas3 = mfspr(SPRN_MAS3);
#ifdef CONFIG_64BIT
	mas7_mas3 = mfspr(SPRN_MAS7_MAS3);
#else
	mas7_mas3 = ((u64)mfspr(SPRN_MAS7) << 32) | mas3;
#endif
	local_irq_restore(flags);

	/*
	 * If the TLB entry for guest pc was evicted, return to the guest.
	 * There are high chances to find a valid TLB entry next time.
	 */
	if (!(mas1 & MAS1_VALID))
		return EMULATE_AGAIN;

	/*
	 * Another thread may rewrite the TLB entry in parallel, don't
	 * execute from the address if the execute permission is not set
	 */
	pr = vcpu->arch.shared->msr & MSR_PR;
	if (unlikely((pr && !(mas3 & MAS3_UX)) ||
		     (!pr && !(mas3 & MAS3_SX)))) {
		pr_err_ratelimited(
			"%s: Instruction emulation from guest address %08lx without execute permission\n",
			__func__, geaddr);
		return EMULATE_AGAIN;
	}

	/*
	 * The real address will be mapped by a cacheable, memory coherent,
	 * write-back page. Check for mismatches when LRAT is used.
	 */
	if (has_feature(vcpu, VCPU_FTR_MMU_V2) &&
	    unlikely((mas2 & MAS2_I) || (mas2 & MAS2_W) || !(mas2 & MAS2_M))) {
		pr_err_ratelimited(
			"%s: Instruction emulation from guest address %08lx mismatches storage attributes\n",
			__func__, geaddr);
		return EMULATE_AGAIN;
	}

	/* Get pfn */
	psize_shift = MAS1_GET_TSIZE(mas1) + 10;
	addr = (mas7_mas3 & (~0ULL << psize_shift)) |
	       (geaddr & ((1ULL << psize_shift) - 1ULL));
	pfn = addr >> PAGE_SHIFT;

	/* Guard against emulation from devices area */
	if (unlikely(!page_is_ram(pfn))) {
		pr_err_ratelimited("%s: Instruction emulation from non-RAM host address %08llx is not supported\n",
			 __func__, addr);
		return EMULATE_AGAIN;
	}

	/* Map a page and get guest's instruction */
	page = pfn_to_page(pfn);
	eaddr = (unsigned long)kmap_atomic(page);
	*instr = *(u32 *)(eaddr | (unsigned long)(addr & ~PAGE_MASK));
	kunmap_atomic((u32 *)eaddr);

	return EMULATE_DONE;
}
