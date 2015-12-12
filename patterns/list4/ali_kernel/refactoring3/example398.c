switch (shift) {
#ifndef CONFIG_PPC_64K_PAGES
	case PAGE_SHIFT_64K:
	    return MMU_PAGE_64K;
#endif
	case PAGE_SHIFT_16M:
	    return MMU_PAGE_16M;
	case PAGE_SHIFT_16G:
	    return MMU_PAGE_16G;
	}
