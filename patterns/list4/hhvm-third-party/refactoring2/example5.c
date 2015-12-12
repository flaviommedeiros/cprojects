#if defined COMPILE_PCRE8
if ((options & PCRE_UTF8) == 0)
#endif
  if (end > 0xff) end = 0xff;
