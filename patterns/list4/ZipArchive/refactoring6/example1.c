if ((method != 0) &&
#ifdef HAVE_BZIP2
        (method != Z_BZIP2ED) &&
#endif
        (method != Z_DEFLATED))
        return ZIP_PARAMERROR;
