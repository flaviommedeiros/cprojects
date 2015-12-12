static int tce_build_wsp(struct iommu_table *tbl, long index, long npages,
			   unsigned long uaddr, enum dma_data_direction direction,
			   struct dma_attrs *attrs)
{
	struct wsp_dma_table *ptbl = container_of(tbl,
						    struct wsp_dma_table,
						    table);
	u64 proto_tce;
	u64 *tcep;
	u64 rpn;

	proto_tce = TCE_PCI_READ;
#ifdef CONFIG_WSP_DD1_WORKAROUND_DD1_TCE_BUGS
	proto_tce |= TCE_PCI_WRITE;
#else
	if (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;
#endif

	/* XXX Make this faster by factoring out the page address for
	 * within a TCE table
	 */
	while (npages--) {
		/* We don't use it->base as the table can be scattered */
		tcep = (u64 *)page_address(ptbl->tces[index >> 16]);
		tcep += (index & 0xffff);

		/* can't move this out since we might cross LMB boundary */
		rpn = __pa(uaddr) >> TCE_SHIFT;
		*tcep = proto_tce | (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT;

		dma_debug("[DMA] TCE %p set to 0x%016llx (dma addr: 0x%lx)\n",
			  tcep, *tcep, (tbl->it_offset + index) << IOMMU_PAGE_SHIFT);

		uaddr += TCE_PAGE_SIZE;
		index++;
	}
	return 0;
}
