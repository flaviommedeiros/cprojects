static int
ccio_map_sg(struct device *dev, struct scatterlist *sglist, int nents, 
	    enum dma_data_direction direction)
{
	struct ioc *ioc;
	int coalesced, filled = 0;
	unsigned long flags;
	unsigned long hint = hint_lookup[(int)direction];
	unsigned long prev_len = 0, current_len = 0;
	int i;
	
	BUG_ON(!dev);
	ioc = GET_IOC(dev);
	
	DBG_RUN_SG("%s() START %d entries\n", __func__, nents);

	/* Fast path single entry scatterlists. */
	if (nents == 1) {
		sg_dma_address(sglist) = ccio_map_single(dev,
				(void *)sg_virt_addr(sglist), sglist->length,
				direction);
		sg_dma_len(sglist) = sglist->length;
		return 1;
	}

	for(i = 0; i < nents; i++)
		prev_len += sglist[i].length;
	
	spin_lock_irqsave(&ioc->res_lock, flags);

#ifdef CCIO_COLLECT_STATS
	ioc->msg_calls++;
#endif

	/*
	** First coalesce the chunks and allocate I/O pdir space
	**
	** If this is one DMA stream, we can properly map using the
	** correct virtual address associated with each DMA page.
	** w/o this association, we wouldn't have coherent DMA!
	** Access to the virtual address is what forces a two pass algorithm.
	*/
	coalesced = iommu_coalesce_chunks(ioc, dev, sglist, nents, ccio_alloc_range);

	/*
	** Program the I/O Pdir
	**
	** map the virtual addresses to the I/O Pdir
	** o dma_address will contain the pdir index
	** o dma_len will contain the number of bytes to map 
	** o page/offset contain the virtual address.
	*/
	filled = iommu_fill_pdir(ioc, sglist, nents, hint, ccio_io_pdir_entry);

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	BUG_ON(coalesced != filled);

	DBG_RUN_SG("%s() DONE %d mappings\n", __func__, filled);

	for (i = 0; i < filled; i++)
		current_len += sg_dma_len(sglist + i);

	BUG_ON(current_len != prev_len);

	return filled;
}
