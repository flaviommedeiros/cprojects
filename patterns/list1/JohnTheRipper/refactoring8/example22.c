static DYNAMIC_primitive_funcp _Funcs_6[] =
{
	//MGF_KEYS_BASE16_IN1_MD5
#if ARCH_LITTLE_ENDIAN
	DynamicFunc__set_input_len_32_cleartop,
	DynamicFunc__append_salt,
	DynamicFunc__crypt_md5,
#else
	DynamicFunc__clean_input2,
	DynamicFunc__append_input2_from_input,
	DynamicFunc__append_salt2,
	DynamicFunc__crypt_md5_in2_to_out1,
#endif
	NULL
};
