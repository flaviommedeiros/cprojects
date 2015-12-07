#ifdef NFLASH_SUPPORT
if (nfl_info) {
			uint32 blocksize;

			blocksize = nfl_info->blocksize;
			off = blocksize;
			for (; off < nfl_boot_size(nfl_info); off += blocksize) {
				if (hndnand_checkbadb(nfl_info, off) != 0)
					continue;
				nvh = (struct nvram_header *)OSL_UNCACHED(flbase + off);
				if (nvh->magic != NVRAM_MAGIC)
					continue;

				/* Read into the nand_nvram */
				if ((nvh = nand_find_nvram(nfl_info, off)) == NULL)
					continue;
				if (nvram_calc_crc(nvh) == (uint8)nvh->crc_ver_init)
					return nvh;
			}
		}
		else
#endif /* NFLASH_SUPPORT */
		{
			off = FLASH_MIN;
			while (off <= lim) {
				nvh = (struct nvram_header *)
					OSL_UNCACHED(flbase + off - MAX_NVRAM_SPACE);
				if (nvh->magic == NVRAM_MAGIC) {
					if (nvram_calc_crc(nvh) == (uint8) nvh->crc_ver_init) {
						return (nvh);
					}
				}
				off <<= 1;
			}
		}
