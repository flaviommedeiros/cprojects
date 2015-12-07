#ifdef PKZIP_BUG_WORKAROUND
if (nl > 288 || nd > 32)
#else
  if (nl > 286 || nd > 30)
#endif
    return 1;
