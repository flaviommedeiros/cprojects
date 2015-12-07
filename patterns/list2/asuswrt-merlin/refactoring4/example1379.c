#ifdef DMA
if (*(uint *)(etc->txavail[priq]) == 0)
#else /* DMA */
		if (etc->pioactive != NULL)
#endif /* DMA */
			break;
