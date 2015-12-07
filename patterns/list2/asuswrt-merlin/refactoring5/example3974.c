#ifdef __BIG_ENDIAN__
if (addr & 0x1) {
		*(u8*)(M.mem_base + addr + 0) = (val >> 0) & 0xff;
		*(u8*)(M.mem_base + addr + 1) = (val >> 8) & 0xff;
		}
	else
#endif
#if defined(__alpha__) || defined(__alpha)
	 stw_u(val,(u16*)(M.mem_base + addr));
