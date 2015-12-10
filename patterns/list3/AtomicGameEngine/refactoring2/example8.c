#ifdef SUPPORT_UTF
if ((options & PCRE_UTF16) == 0)
#endif
  if (end > 0xffff) end = 0xffff;
