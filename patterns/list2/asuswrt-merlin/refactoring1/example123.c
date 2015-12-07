if (pmem[id].cached == 0 || file->f_flags & O_SYNC)
		return pgprot_noncached(vma_prot);
#endif
#ifdef pgprot_ext_buffered
	else if (pmem[id].buffered)
		return pgprot_ext_buffered(vma_prot);
#endif
