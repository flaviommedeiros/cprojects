#ifdef HAVE_FDOPEN
if (fd != -1)
    nbfd->iostream = fdopen (fd, mode);
  else
#endif
    nbfd->iostream = real_fopen (filename, mode);
