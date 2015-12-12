#ifndef HOST_IS_BIG_ENDIAN
if (state->bigendSig == HIGH)
#else
	if (state->bigendSig != HIGH)
#endif
		*data = ((*data & 0xff) << 24) | 
			 (((*data >> 8) & 0xff) << 16)  |
			 (((*data >> 16) & 0xff) << 8)  |
			 (((*data >> 24) & 0xff));
