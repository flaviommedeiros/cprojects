if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
    {
        int tmp_err = deflateEnd(&zi->ci.stream);
        if (err == ZIP_OK)
            err = tmp_err;
        zi->ci.stream_initialised = 0;
    }
#ifdef HAVE_BZIP2
    else if((zi->ci.method == Z_BZIP2ED) && (!zi->ci.raw))
    {
      int tmperr = BZ2_bzCompressEnd(&zi->ci.bstream);
                        if (err==ZIP_OK)
                                err = tmperr;
                        zi->ci.stream_initialised = 0;
    }
#endif
