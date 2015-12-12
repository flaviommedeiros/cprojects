#ifdef CONFIG_AS_AVX2
if (boot_cpu_has(X86_FEATURE_AVX2)) {
		pr_info("AVX2 version of gcm_enc/dec engaged.\n");
		aesni_gcm_enc_tfm = aesni_gcm_enc_avx2;
		aesni_gcm_dec_tfm = aesni_gcm_dec_avx2;
	} else
#endif
#ifdef CONFIG_AS_AVX
	if (boot_cpu_has(X86_FEATURE_AVX)) {
		pr_info("AVX version of gcm_enc/dec engaged.\n");
		aesni_gcm_enc_tfm = aesni_gcm_enc_avx;
		aesni_gcm_dec_tfm = aesni_gcm_dec_avx;
	} else
#endif
	{
		pr_info("SSE version of gcm_enc/dec engaged.\n");
		aesni_gcm_enc_tfm = aesni_gcm_enc;
		aesni_gcm_dec_tfm = aesni_gcm_dec;
	}
