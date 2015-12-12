#ifndef __BIG_ENDIAN
if (ioread32_native(map + 0x000004) != 0x00000000)
#else
		if (ioread32_native(map + 0x000004) == 0x00000000)
#endif
			iowrite32_native(0x01000001, map + 0x000004);
