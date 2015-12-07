#ifdef HAVE_PREAD64
if (pread64 (fd, readbuf, len, offset) != len)
#else
  if (lseek (fd, offset, SEEK_SET) == -1 || read (fd, readbuf, len) != len)
#endif
    ret = 0;
  else
    ret = len;
