#ifdef __BIG_ENDIAN__
if (addr & 0x1) {
		*(u8*)(M.mem_base + addr + 0) = (val >>  0) & 0xff;
		*(u8*)(M.mem_base + addr + 1) = (val >>  8) & 0xff;
		*(u8*)(M.mem_base + addr + 2) = (val >> 16) & 0xff;
		*(u8*)(M.mem_base + addr + 3) = (val >> 24) & 0xff;
		}
	else
#endif
#if defined(__alpha__) || defined(__alpha)
	 stl_u(val,(u32*)(M.mem_base + addr));
