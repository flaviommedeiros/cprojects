#ifdef SIMD_COEF_64
if (((ARCH_WORD_64*)binary)[3] == crypt_out[HASH_IDX])
#else
		if ( ((ARCH_WORD_64*)binary)[0] == crypt_out[index][0] )
#endif
			return 1;
