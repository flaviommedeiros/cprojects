#ifdef CONFIG_MTD_NFLASH
if (nfl_info != NULL) {
		blocksize = nfl_info->blocksize;
		off = blocksize;
		while (off <= lim) {
			if (nflash_checkbadb(sih, cc, off) != 0) {
				off += blocksize;
				continue;
			}
			header = (struct nvram_header *) KSEG1ADDR(base + off);
			if (header->magic == NVRAM_MAGIC)
				if (nvram_calc_crc(header) == (uint8) header->crc_ver_init) {
					goto found;
				}
			off += blocksize;
		}
	} else
#endif
	{
		off = FLASH_MIN;
		while (off <= lim) {
			/* Windowed flash access */
			header = (struct nvram_header *) KSEG1ADDR(base + off - NVRAM_SPACE);
			if (header->magic == NVRAM_MAGIC)
				if (nvram_calc_crc(header) == (uint8) header->crc_ver_init) {
					goto found;
				}
			off <<= 1;
		}
	}
