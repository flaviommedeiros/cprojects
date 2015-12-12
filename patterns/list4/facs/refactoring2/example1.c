#ifndef __clang__
if (ftruncate64 (fd, total_size) < 0)
  #endif
#endif
  {
      printf ("[%d]-ftruncate64 error: %s/n", errno, strerror (errno));
      close (fd);
      return 0;
  }
