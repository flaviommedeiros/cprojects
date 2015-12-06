if (strm->state->wrap == 1) {
        strm->adler = adler32(strm->adler, strm->next_in, len);
    }
#ifdef GZIP
    else if (strm->state->wrap == 2) {
        strm->adler = crc32(strm->adler, strm->next_in, len);
    }
#endif
