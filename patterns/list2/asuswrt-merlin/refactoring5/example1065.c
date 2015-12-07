#ifdef __BIG_ENDIAN__
if (addr & 0x3) {
		val = (*(u8*)(M.mem_base + addr + 0) |
			  (*(u8*)(M.mem_base + addr + 1) << 8) |
			  (*(u8*)(M.mem_base + addr + 2) << 16) |
			  (*(u8*)(M.mem_base + addr + 3) << 24));
		}
	else
#endif
#if defined(__alpha__) || defined(__alpha)
		val = ldl_u((u32*)(M.mem_base + addr));
