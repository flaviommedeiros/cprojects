#ifdef HAVE_MMAP
if (stream->hints & RFILE_HINT_MMAP)
         return -1;
      else
#endif
         return write(stream->fd, s, len);
