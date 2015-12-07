#if defined(HAVE_GETPT) && defined(linux)
if ((f = getpt()) == -1)
#else
  if ((f = open(PtyName, O_RDWR | O_NOCTTY)) == -1)
#endif
    return -1;
