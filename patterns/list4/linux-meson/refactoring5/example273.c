#ifdef CONFIG_AS_AVX2
if (boot_cpu_has(X86_FEATURE_AVX2))
			sha256_transform_asm = sha256_transform_rorx;
		else
#endif
			sha256_transform_asm = sha256_transform_avx;
