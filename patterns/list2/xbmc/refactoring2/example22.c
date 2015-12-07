#ifdef MSGWINDOW
if(!xskin_ready)
#endif
  {
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, NLS);
    va_end(ap);
    return 0;
  }
