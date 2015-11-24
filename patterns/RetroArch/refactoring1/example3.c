if (windowBits < 0) { /* suppress zlib wrapper */
      wrap = 0;
      windowBits = -windowBits;
   }
#ifdef GZIP
   else if (windowBits > 15) {
      wrap = 2;       /* write gzip wrapper instead */
      windowBits -= 16;
   }
#endif
