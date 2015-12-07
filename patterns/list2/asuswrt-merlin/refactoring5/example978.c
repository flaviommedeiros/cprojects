#ifdef NFLASH_SUPPORT
if (nvram_mtd->type == MTD_NANDFLASH)
			offset = 0;
		else
#endif
			offset = nvram_mtd->size - nvram_space;
