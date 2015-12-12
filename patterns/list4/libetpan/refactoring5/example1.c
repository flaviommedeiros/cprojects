#ifndef MMAP_UNAVAILABLE
if (string->fd != -1) {
    munmap(string->str, string->mmapped_size);
    close(string->fd);
  }
  else
#endif
  {
    free (string->str);
  }
