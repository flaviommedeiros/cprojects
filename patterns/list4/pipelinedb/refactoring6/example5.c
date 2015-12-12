if (
#ifndef WIN32
			*s1 != *s2
#else
		/* On windows, paths are case-insensitive */
			pg_tolower((unsigned char) *s1) != pg_tolower((unsigned char) *s2)
#endif
			&& !(IS_DIR_SEP(*s1) && IS_DIR_SEP(*s2)))
			return (int) *s1 - (int) *s2;
