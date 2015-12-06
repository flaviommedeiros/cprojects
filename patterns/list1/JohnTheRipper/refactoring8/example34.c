static DYNAMIC_primitive_funcp _Funcs_34[] =
{
	//MGF_KEYS_INPUT
	//MGF_SET_INP2LEN32
	DynamicFunc__crypt_md4,
	//DynamicFunc__clean_input2_kwik,
	//DynamicFunc__append_from_last_output_to_input2_as_base16,
	DynamicFunc__overwrite_from_last_output_to_input2_as_base16_no_size_fix,
#if !ARCH_LITTLE_ENDIAN
	DynamicFunc__set_input2_len_32_cleartop,
#endif
	DynamicFunc__crypt_md5_in2_to_out1,
	NULL
};
