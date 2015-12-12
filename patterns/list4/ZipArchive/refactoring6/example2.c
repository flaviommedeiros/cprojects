if ((err == UNZ_OK) && (compression_method != 0) &&
#ifdef HAVE_BZIP2
        (compression_method != Z_BZIP2ED) &&
#endif
        (compression_method != Z_DEFLATED))
        err = UNZ_BADZIPFILE;
