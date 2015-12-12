if ((
#ifndef USE_CRNL_AS_LINE_TERMINATOR
	 *(p+3) == 0x0d ||
#endif
	 *(p+3) == 0x85)
	&& *(p+2) == 0 && *(p+1) == 0 && *p == 0x00)
      return 1;
