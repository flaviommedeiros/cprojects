switch(c)
  {
#ifdef EBCDIC
  case CHAR_NEL:
#endif
  case CHAR_LF:
  case CHAR_VT:
  case CHAR_FF: *lenptr = 1; return TRUE;

  case CHAR_CR:
  *lenptr = (ptr < endptr - 1 && ptr[1] == CHAR_LF)? 2 : 1;
  return TRUE;

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
#endif  /* Not EBCDIC */

  default: return FALSE;
  }
