#ifdef SIMD_COEF_32
if (*((uint32_t*)binary) == crypt_out[HASH_IDX_OUT])
#else
		if (*((ARCH_WORD_32*)binary) == crypt_out[index][0])
#endif
			return 1;
