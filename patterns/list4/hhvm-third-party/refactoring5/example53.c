#ifdef SUPPORT_LIBZ
if (pathlen > 3 && strcmp(pathname + pathlen - 3, ".gz") == 0)
  {
  ingz = gzopen(pathname, "rb");
  if (ingz == NULL)
    {
    if (!silent)
      fprintf(stderr, "pcregrep: Failed to open %s: %s\n", pathname,
        strerror(errno));
    return 2;
    }
  handle = (void *)ingz;
  frtype = FR_LIBZ;
  }
else
#endif

/* Otherwise open with bz2lib if it is supported and the name ends with .bz2. */

#ifdef SUPPORT_LIBBZ2
if (pathlen > 4 && strcmp(pathname + pathlen - 4, ".bz2") == 0)
  {
  inbz2 = BZ2_bzopen(pathname, "rb");
  handle = (void *)inbz2;
  frtype = FR_LIBBZ2;
  }
else
#endif

/* Otherwise use plain fopen(). The label is so that we can come back here if
an attempt to read a .bz2 file indicates that it really is a plain file. */

#ifdef SUPPORT_LIBBZ2
PLAIN_FILE:
#endif
  {
  in = fopen(pathname, "rb");
  handle = (void *)in;
  frtype = FR_PLAIN;
  }
