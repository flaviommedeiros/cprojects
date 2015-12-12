switch(c)
  {
  case CHAR_LF:
  *lenptr = (ptr > startptr && ptr[-1] == CHAR_CR)? 2 : 1;
  return TRUE;

#ifdef EBCDIC
  case CHAR_NEL:
#endif
  case CHAR_VT:
  case CHAR_FF:
  case CHAR_CR: *lenptr = 1; return TRUE;

#ifndef EBCDIC
#ifdef COMPILE_PCRE8
  case CHAR_NEL: *lenptr = utf? 2 : 1; return TRUE;
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 3; return TRUE;             /* PS */
#else /* COMPILE_PCRE16 || COMPILE_PCRE32 */
  case CHAR_NEL:
  case 0x2028:                                       /* LS */
  case 0x2029: *lenptr = 1; return TRUE;             /* PS */
#endif  /* COMPILE_PCRE8 */
#endif  /* NotEBCDIC */

  default: return FALSE;
  }
