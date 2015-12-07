if (iova_space_size < (1 << (20 - PAGE_SHIFT))) {
		iova_space_size =  1 << (20 - PAGE_SHIFT);
#ifdef __LP64__
	} else if (iova_space_size > (1 << (30 - PAGE_SHIFT))) {
		iova_space_size =  1 << (30 - PAGE_SHIFT);
#endif
	}
#endif
