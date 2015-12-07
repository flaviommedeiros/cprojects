#ifdef CFG_NFLASH
if (bootdev == SOC_BOOTDEV_NANDFLASH) {
		nfl_info = hndnand_init(sih);
		if (!nfl_info)
			return;

		fprobe.flash_phys = nfl_info->phybase;
		drv = &nflashdrv;
	} else
#endif	/* CFG_NFLASH */
#if CFG_SFLASH
	if (bootdev == SOC_BOOTDEV_SFLASH) {
		sfl_info = hndsflash_init(sih);
		if (!sfl_info)
			return;

		fprobe.flash_phys = sfl_info->phybase;
		drv = &sflashdrv;
	}
	else
#endif
#if CFG_FLASH
	{
		/* This might be wrong, but set pflash
		 * as default if nothing configured
		 */
		chipcregs_t *cc;

		if ((cc = (chipcregs_t *)si_setcoreidx(sih, SI_CC_IDX)) == NULL)
			return;

		fprobe.flash_phys = SI_FLASH2;
		fprobe.flash_flags = FLASH_FLG_BUS16 | FLASH_FLG_DEV16;
		if (!(R_REG(NULL, &cc->flash_config) & CC_CFG_DS))
			fprobe.flash_flags = FLASH_FLG_BUS8 | FLASH_FLG_DEV16;
		drv = &newflashdrv;
	}
