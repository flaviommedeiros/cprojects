#if defined(__LITTLE_ENDIAN)
if (self->func->bits_per_word == 8)
#endif
	{
		uint16_t *buf = (uint16_t *)dst;
		for (i = 0; i < ((count + 1) >> 1); i++)
			buf[i] = swab16(buf[i]);
	}
