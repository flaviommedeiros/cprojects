#ifdef CONFIG_MTD_NFLASH
if (bootdev == SOC_BOOTDEV_NANDFLASH) {
		if ((nfl_info = hndnand_init(sih)) == NULL)
			return -1;
		flash_base = nfl_info->base;
		blocksize = nfl_info->blocksize;
		off = blocksize;
		for (; off < nfl_boot_size(nfl_info); off += blocksize) {
			if (hndnand_checkbadb(nfl_info, off) != 0)
				continue;
			header = (struct nvram_header *)(flash_base + off);
			if (header->magic != NVRAM_MAGIC)
				continue;

			/* Read into the nand_nvram */
			if ((header = nand_find_nvram(nfl_info, off)) == NULL)
				continue;
			if (nvram_calc_crc(header) == (uint8)header->crc_ver_init)
				goto found;
		}
	}
	else
#endif
	if (bootdev == SOC_BOOTDEV_SFLASH ||
	    bootdev == SOC_BOOTDEV_ROM) {
		/* Boot from SFLASH or ROM */
		if ((sfl_info = hndsflash_init(sih)) == NULL)
			return -1;

		lim = sfl_info->size;

		BUG_ON(request_resource(&iomem_resource, &norflash_region));
	
		flash_base = sfl_info->base;
	
		BUG_ON(IS_ERR_OR_NULL((void *)flash_base));
		
		off = FLASH_MIN;
		while (off <= lim) {
			/* Windowed flash access */
			header = (struct nvram_header *)(flash_base + off - nvram_space);
			if (header->magic == NVRAM_MAGIC)
				if (nvram_calc_crc(header) == (uint8)header->crc_ver_init) {
					goto found;
				}
			off += DEF_NVRAM_SPACE;
		}
	}
	else {
		/* This is the case bootdev == SOC_BOOTDEV_PFLASH, not applied on NorthStar */
		ASSERT(0);
	}
