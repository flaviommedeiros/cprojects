#if(__SIZEOF_INT__ >= 4)
if (a > (unsigned short)b)
#else
  if ((long) a > (unsigned short)b)
#endif
    abort ();
