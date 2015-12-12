#ifdef CONFIG_HUGETLB_PAGE
if (unlikely(mmu_huge_psizes[psize])) {
		pte_t *ptep;
		unsigned long a = addr;
		unsigned long sz = ((1UL) << shift);
		struct hstate *hstate = size_to_hstate(sz);

		BUG_ON(!hstate);
		/*
		 * XXX: could be optimized to avoid hstate
		 * lookup entirely (just use shift)
		 */

		do {
			VM_BUG_ON(shift != mmu_psize_defs[get_slice_psize(mm, a)].shift);
			ptep = huge_pte_offset(mm, a);
			pr_devel(" %016lx: huge ptep %p\n", a, ptep);
			if (!ptep || !gup_huge_pte(ptep, hstate, &a, end, write, pages,
						   &nr))
				goto slow;
		} while (a != end);
	} else
#endif /* CONFIG_HUGETLB_PAGE */
	{
		pgdp = pgd_offset(mm, addr);
		do {
			pgd_t pgd = *pgdp;

#ifdef CONFIG_PPC64
			VM_BUG_ON(shift != mmu_psize_defs[get_slice_psize(mm, addr)].shift);
#endif
			pr_devel("  %016lx: normal pgd %p\n", addr,
				 (void *)pgd_val(pgd));
			next = pgd_addr_end(addr, end);
			if (pgd_none(pgd))
				goto slow;
			if (!gup_pud_range(pgd, addr, next, write, pages, &nr))
				goto slow;
		} while (pgdp++, addr = next, addr != end);
	}
