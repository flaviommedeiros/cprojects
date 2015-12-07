#if NEED_HANDLE_LARGE_LONG
if (BITS_PER_LONG > 32)
#endif
    while (x >= 0x100000000L)
      {
	x >>= 32;
	i += 32;
      }
