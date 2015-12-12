#ifdef WORDS_BIGENDIAN
if (endian == 1)
#else
   if (endian == 0)
#endif
   {
      // should setup reading so it's byte-swapped
      YabSetError(YAB_ERR_OTHER, (void *)"Load State byteswapping not supported");
      return -3;
   }
