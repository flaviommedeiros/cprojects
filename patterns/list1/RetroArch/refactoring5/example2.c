#ifdef HAVE_MMAP
if (stream->hints & RFILE_HINT_MMAP && (stream->hints & 0xff) == RFILE_MODE_READ)
      stream->hints |= RFILE_HINT_UNBUFFERED;
   else
#endif
      stream->hints &= ~RFILE_HINT_MMAP;
