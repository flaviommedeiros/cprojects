#ifdef SIMD_COEF_32
if (((ARCH_WORD_32 *) binary)[0] == ((ARCH_WORD_32*)crypt_key)[(index&(SIMD_COEF_32-1)) + index/SIMD_COEF_32*5*SIMD_COEF_32])
#else
		if ( ((ARCH_WORD_32*)binary)[0] == ((ARCH_WORD_32*)&(crypt_key[index][0]))[0] )
#endif
			return 1;
