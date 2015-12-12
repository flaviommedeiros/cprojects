#ifdef CONFIG_PPC_64K_PAGES
if (psize == MMU_PAGE_64K)
		rc = __hash_page_64K(ea, access, vsid, ptep, trap,
				     flags, ssize);
	else
#endif /* CONFIG_PPC_64K_PAGES */
	{
		int spp = subpage_protection(mm, ea);
		if (access & spp)
			rc = -2;
		else
			rc = __hash_page_4K(ea, access, vsid, ptep, trap,
					    flags, ssize, spp);
	}
