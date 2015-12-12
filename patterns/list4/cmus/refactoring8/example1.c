pcm_conv_in_place_func pcm_conv_in_place[8] = {
	NULL,
	NULL,
	NULL,
	NULL,

	convert_u16_le_to_s16_le,
	convert_u16_be_to_s16_le,

#ifdef WORDS_BIGENDIAN
	swap_s16_byte_order,
	NULL,
#else
	NULL,
	swap_s16_byte_order,
#endif
};
