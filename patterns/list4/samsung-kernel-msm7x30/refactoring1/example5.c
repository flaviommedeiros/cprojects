if (pmem[id].cached == 0 || file->f_flags & O_SYNC)
		/* on ARMv6 and ARMv7 this expands to Normal Noncached */
		return pgprot_writecombine(vma_prot);
#endif
#ifdef pgprot_ext_buffered
	else if (pmem[id].buffered)
		return pgprot_ext_buffered(vma_prot);
#endif
