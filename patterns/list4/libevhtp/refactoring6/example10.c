if ((
#ifndef USE_CRNL_AS_LINE_TERMINATOR
	 *(p+1) == 0x0d ||
#endif
	 *(p+1) == 0x85) && *p == 0x00)
      return 1;
