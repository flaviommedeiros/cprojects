static const char *pgtable_cache_name[ARRAY_SIZE(pgtable_cache_size)] = {
#ifdef CONFIG_PPC_64K_PAGES
	"pgd_cache", "pmd_cache",
#else
	"pgd_cache", "pud_pmd_cache",
#endif /* CONFIG_PPC_64K_PAGES */
};
