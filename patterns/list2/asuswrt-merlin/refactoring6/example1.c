if (!(len == 1)		/* "/" */
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
	  && !(len == 3 && dir[1] == ':') /* "d:/" */
#endif
	  )
	len--;
