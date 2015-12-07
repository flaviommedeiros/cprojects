#ifdef NFLASH_SUPPORT
if (bootdev == SOC_BOOTDEV_NANDFLASH) {
		/* Init nand anyway */
		nfl_info = hndnand_init(sih);
		if (nfl_info)
			flbase = nfl_info->phybase;
	}
	else
#endif /* NFLASH_SUPPORT */
	if (bootdev == SOC_BOOTDEV_SFLASH) {
#ifdef _CFE_
		/* Init nand anyway */
		sfl_info = hndsflash_init(sih);
		if (sfl_info) {
			flbase = sfl_info->phybase;
			lim = sfl_info->size;
		}
#else
	if (sih->ccrev == 42)
		flbase = SI_NS_NORFLASH;
#endif
	}
