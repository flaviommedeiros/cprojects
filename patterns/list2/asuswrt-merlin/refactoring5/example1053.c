#ifdef CONFIG_PPC_HAS_HASH_64K
if (psize == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap, local);
	else
#endif /* CONFIG_PPC_HAS_HASH_64K */
		rc = __hash_page_4K(ea, access, vsid, ptep, trap, local);
