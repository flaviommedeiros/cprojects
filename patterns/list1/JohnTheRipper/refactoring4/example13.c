#ifdef SIMD_COEF_64
if (((ARCH_WORD_64 *) binary)[0] == crypt_out[index/SIMD_COEF_64][index&(SIMD_COEF_64-1)])
#else
		if ( ((ARCH_WORD_32*)binary)[0] == crypt_out[index][0] )
#endif
			return 1;
