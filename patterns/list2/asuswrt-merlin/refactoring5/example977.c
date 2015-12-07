#ifdef NFLASH_SUPPORT
if (nfl_info != NULL) {
		blocksize = nfl_info->blocksize;
		off = blocksize;
		while (off <= lim) {
			if (nflash_checkbadb(sih, cc, off) != 0) {
				off += blocksize;
				continue;
			}
			header = (struct nvram_header *) KSEG1ADDR(base + off);
			if (header->magic != NVRAM_MAGIC)
				continue;

			/* Read into the nand_nvram */
			if ((header = nand_find_nvram(nfl_info, off)) == NULL)
				continue;
			if (nvram_calc_crc(header) == (uint8)header->crc_ver_init)
				goto found;
		}
	} else
#endif
	{
		off = FLASH_MIN;

#ifdef RTN66U_NVRAM_64K_SUPPORT
		header = (struct nvram_header *) KSEG1ADDR(base + lim - 0x8000);
		if(header->magic==0xffffffff) {
			header = (struct nvram_header *) KSEG1ADDR(base + 1 KB);
			if (nvram_calc_crc(header) == (uint8) header->crc_ver_init) {
				nvram_32_reset=1;
				goto found;
			}
		}
#endif

		while (off <= lim) {
			/* Windowed flash access */
			header = (struct nvram_header *) KSEG1ADDR(base + off - MAX_NVRAM_SPACE);
			if (header->magic == NVRAM_MAGIC)
				if (nvram_calc_crc(header) == (uint8) header->crc_ver_init) {
					goto found;
				}
			off += DEF_NVRAM_SPACE;
		}
	}
