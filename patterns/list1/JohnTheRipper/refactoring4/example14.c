#if ARCH_ALLOWS_UNALIGNED
if (*((ARCH_WORD_32*)cpsalt) != 0x30303030)
#else
	if (memcmp(cpsalt, "0000", 4))
#endif
	{
		// this is why we used base-8. Takes an extra byte, but there is NO conditional
		// logic, building this number, and no multiplication. We HAVE added one conditional
		// check, to see if we can skip the entire load, if it is 0000.
		todo_bits = *cpsalt++ - '0';
		todo_bits <<= 3;
		todo_bits += *cpsalt++ - '0';
		todo_bits <<= 3;
		todo_bits += *cpsalt++ - '0';
		todo_bits <<= 3;
		todo_bits += *cpsalt++ - '0';
	}
	else
		cpsalt += 4;
