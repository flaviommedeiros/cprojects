#ifdef __BIG_ENDIAN__
if (addr & 0x1) {
		val = (*(u8*)(M.mem_base + addr) |
			  (*(u8*)(M.mem_base + addr + 1) << 8));
		}
	else
#endif
#if defined(__alpha__) || defined(__alpha)
		val = ldw_u((u16*)(M.mem_base + addr));
