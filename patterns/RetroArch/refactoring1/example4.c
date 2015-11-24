if (state->wrap == 1) {
      strm->adler = adler32(strm->adler, buf, len);
   }
#ifdef GZIP
   else if (state->wrap == 2) {
      strm->adler = crc32(strm->adler, buf, len);
   }
#endif
