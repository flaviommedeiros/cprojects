static DYNAMIC_primitive_funcp _Funcs_2[] =
{
	//MGF_KEYS_INPUT
	//MGF_SET_INP2LEN32
	DynamicFunc__crypt_md5,
	DynamicFunc__overwrite_from_last_output_to_input2_as_base16_no_size_fix,
#if !ARCH_LITTLE_ENDIAN
	// Not sure WHY this is needed in BE systems, BUT it is???
	// it does do a memset on last part of buffer, but 'why' is that needed???
	// we should have a fixed length of 32 bytes set, so not sure why we need
	// to continue to clear on these formats.
	DynamicFunc__set_input2_len_32_cleartop,
#endif

	DynamicFunc__crypt_md5_in2_to_out1,
	NULL
};
