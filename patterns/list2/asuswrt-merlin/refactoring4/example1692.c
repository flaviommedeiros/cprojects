#ifdef XZ_DEC_BCJ
if (s->temp.buf[1] & 0x3E)
#else
	if (s->temp.buf[1] & 0x3F)
#endif
		return XZ_OPTIONS_ERROR;
