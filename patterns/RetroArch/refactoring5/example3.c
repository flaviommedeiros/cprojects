#ifdef HAVE_MMAP
if (stream->hints & RFILE_HINT_MMAP)
      {
         if (stream->mappos > stream->mapsize)
            return -1;

         if (stream->mappos + len > stream->mapsize)
            len = stream->mapsize - stream->mappos;

         memcpy(s, &stream->mapped[stream->mappos], len);
         stream->mappos += len;

         return len;
      }
      else
#endif
         return read(stream->fd, s, len);
