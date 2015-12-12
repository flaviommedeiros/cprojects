static const UnsupportedFunction unsupported_functions[] =
  {
#if defined (HAVE_I386)
    { "ret",   1, 0, { 0xc3                                           } },
    { "retf",  1, 0, { 0xcb                                           } },
#elif defined (HAVE_ARM)
    { "ret",   2, 1, { 0x70, 0x47                                     } },
#endif
  };
