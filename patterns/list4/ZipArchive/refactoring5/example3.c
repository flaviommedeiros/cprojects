#ifdef HAVE_BZIP2
if (zi->ci.compression_method == Z_BZIP2ED) {
        zi->ci.total_uncompressed += zi->ci.bstream.total_in_lo32;
        zi->ci.bstream.total_in_lo32 = 0;
        zi->ci.bstream.total_in_hi32 = 0;
    } else
#endif
    {
        zi->ci.total_uncompressed += zi->ci.stream.total_in;
        zi->ci.stream.total_in = 0;
    }
