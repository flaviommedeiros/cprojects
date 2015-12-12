#ifdef CONFIG_TRANSPARENT_HUGEPAGE
if (pmd_trans_huge(*pmdp)) {
		if (pmd_trans_splitting(*pmdp))
			goto out_irq_enable;

		pa  = pmd_pfn(*pmdp) << PAGE_SHIFT;
		pa += tpc & ~HPAGE_MASK;

		/* Use phys bypass so we don't pollute dtlb/dcache. */
		__asm__ __volatile__("lduwa [%1] %2, %0"
				     : "=r" (insn)
				     : "r" (pa), "i" (ASI_PHYS_USE_EC));
	} else
#endif
	{
		ptep = pte_offset_map(pmdp, tpc);
		pte = *ptep;
		if (pte_present(pte)) {
			pa  = (pte_pfn(pte) << PAGE_SHIFT);
			pa += (tpc & ~PAGE_MASK);

			/* Use phys bypass so we don't pollute dtlb/dcache. */
			__asm__ __volatile__("lduwa [%1] %2, %0"
					     : "=r" (insn)
					     : "r" (pa), "i" (ASI_PHYS_USE_EC));
		}
		pte_unmap(ptep);
	}
