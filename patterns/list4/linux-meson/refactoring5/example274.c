#ifdef CONFIG_AS_AVX2
if (boot_cpu_has(X86_FEATURE_AVX2))
			sha512_transform_asm = sha512_transform_rorx;
		else
#endif
			sha512_transform_asm = sha512_transform_avx;
