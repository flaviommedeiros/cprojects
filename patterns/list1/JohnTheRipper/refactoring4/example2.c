#ifdef SIMD_COEF_32
if (((ARCH_WORD_32*) binary)[0] == crypt_out[HASH_IDX])
#else
		if ( ((ARCH_WORD_32*)binary)[0] == crypt_out[index][0] )
#endif
			return 1;
