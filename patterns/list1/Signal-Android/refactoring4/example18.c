#ifndef CHARSET_EBCDIC
if (*type == '+')
#else
		if (*type == os_toascii['+'])
#endif
			{
			mval = -1;
			type++;
			}
		else
			mval = 0;
