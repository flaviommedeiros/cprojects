#ifdef CONFIG_X86_64
if (unlikely(pmd_large(*pmdp)))
		pte = *(pte_t *) pmdp;
	else
#endif
		pte = *pte_offset_kernel(pmdp, vaddr);
