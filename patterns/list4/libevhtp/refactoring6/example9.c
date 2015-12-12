if ((
#ifndef USE_CRNL_AS_LINE_TERMINATOR
	 *p == 0x0d ||
#endif
	 *p == 0x85)
	&& *(p+1) == 0x00 && (p+2) == 0x00 && *(p+3) == 0x00)
      return 1;
