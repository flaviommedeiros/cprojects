#ifdef NFLASH_SUPPORT
if (bootdev == SOC_BOOTDEV_NANDFLASH) {
		flbase = SI_NS_NANDFLASH;
		goto embedded_nv;
	}
	else
#endif /* NFLASH_SUPPORT */
	{
		/* bootdev == SOC_BOOTDEV_SFLASH */
		flbase = SI_NS_NORFLASH;
		off = FLASH_MIN;
		while (off <= SI_NS_FLASH_WINDOW) {
			nvh = (struct nvram_header *)(flbase + off - MAX_NVRAM_SPACE);
			if (R_REG(osh, &nvh->magic) == NVRAM_MAGIC)
				break;
			off += DEF_NVRAM_SPACE;
			nvh = NULL;
		};
	}
