static int tce_build_cell(struct iommu_table *tbl, long index, long npages,
		unsigned long uaddr, enum dma_data_direction direction,
		struct dma_attrs *attrs)
{
	int i;
	unsigned long *io_pte, base_pte;
	struct iommu_window *window =
		container_of(tbl, struct iommu_window, table);

	/* implementing proper protection causes problems with the spidernet
	 * driver - check mapping directions later, but allow read & write by
	 * default for now.*/
#ifdef CELL_IOMMU_STRICT_PROTECTION
	/* to avoid referencing a global, we use a trick here to setup the
	 * protection bit. "prot" is setup to be 3 fields of 4 bits apprended
	 * together for each of the 3 supported direction values. It is then
	 * shifted left so that the fields matching the desired direction
	 * lands on the appropriate bits, and other bits are masked out.
	 */
	const unsigned long prot = 0xc48;
	base_pte =
		((prot << (52 + 4 * direction)) &
		 (CBE_IOPTE_PP_W | CBE_IOPTE_PP_R)) |
		CBE_IOPTE_M | CBE_IOPTE_SO_RW |
		(window->ioid & CBE_IOPTE_IOID_Mask);
#else
	base_pte = CBE_IOPTE_PP_W | CBE_IOPTE_PP_R | CBE_IOPTE_M |
		CBE_IOPTE_SO_RW | (window->ioid & CBE_IOPTE_IOID_Mask);
#endif
	if (unlikely(dma_get_attr(DMA_ATTR_WEAK_ORDERING, attrs)))
		base_pte &= ~CBE_IOPTE_SO_RW;

	io_pte = (unsigned long *)tbl->it_base + (index - tbl->it_offset);

	for (i = 0; i < npages; i++, uaddr += (1 << tbl->it_page_shift))
		io_pte[i] = base_pte | (__pa(uaddr) & CBE_IOPTE_RPN_Mask);

	mb();

	invalidate_tce_cache(window->iommu, io_pte, npages);

	pr_debug("tce_build_cell(index=%lx,n=%lx,dir=%d,base_pte=%lx)\n",
		 index, npages, direction, base_pte);
	return 0;
}
