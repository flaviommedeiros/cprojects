static dma_addr_t 
ccio_map_single(struct device *dev, void *addr, size_t size,
		enum dma_data_direction direction)
{
	int idx;
	struct ioc *ioc;
	unsigned long flags;
	dma_addr_t iovp;
	dma_addr_t offset;
	u64 *pdir_start;
	unsigned long hint = hint_lookup[(int)direction];

	BUG_ON(!dev);
	ioc = GET_IOC(dev);

	BUG_ON(size <= 0);

	/* save offset bits */
	offset = ((unsigned long) addr) & ~IOVP_MASK;

	/* round up to nearest IOVP_SIZE */
	size = ALIGN(size + offset, IOVP_SIZE);
	spin_lock_irqsave(&ioc->res_lock, flags);

#ifdef CCIO_COLLECT_STATS
	ioc->msingle_calls++;
	ioc->msingle_pages += size >> IOVP_SHIFT;
#endif

	idx = ccio_alloc_range(ioc, dev, size);
	iovp = (dma_addr_t)MKIOVP(idx);

	pdir_start = &(ioc->pdir_base[idx]);

	DBG_RUN("%s() 0x%p -> 0x%lx size: %0x%x\n",
		__func__, addr, (long)iovp | offset, size);

	/* If not cacheline aligned, force SAFE_DMA on the whole mess */
	if((size % L1_CACHE_BYTES) || ((unsigned long)addr % L1_CACHE_BYTES))
		hint |= HINT_SAFE_DMA;

	while(size > 0) {
		ccio_io_pdir_entry(pdir_start, KERNEL_SPACE, (unsigned long)addr, hint);

		DBG_RUN(" pdir %p %08x%08x\n",
			pdir_start,
			(u32) (((u32 *) pdir_start)[0]),
			(u32) (((u32 *) pdir_start)[1]));
		++pdir_start;
		addr += IOVP_SIZE;
		size -= IOVP_SIZE;
	}

	spin_unlock_irqrestore(&ioc->res_lock, flags);

	/* form complete address */
	return CCIO_IOVA(iovp, offset);
}
