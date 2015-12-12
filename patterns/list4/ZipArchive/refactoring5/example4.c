#ifdef HAVE_BZIP2
if ((zi->ci.compression_method == Z_BZIP2ED) && (!zi->ci.raw)) {
        zi->ci.bstream.next_in = (void *)buf;
        zi->ci.bstream.avail_in = len;
        err = BZ_RUN_OK;

        while ((err == BZ_RUN_OK) && (zi->ci.bstream.avail_in > 0)) {
            if (zi->ci.bstream.avail_out == 0) {
                if (zip64FlushWriteBuffer(zi) == ZIP_ERRNO)
                    err = ZIP_ERRNO;
                zi->ci.bstream.avail_out = (uInt)Z_BUFSIZE;
                zi->ci.bstream.next_out = (char *)zi->ci.buffered_data;
            } else {
                uLong uTotalOutBefore_lo = zi->ci.bstream.total_out_lo32;
                uLong uTotalOutBefore_hi = zi->ci.bstream.total_out_hi32;

                err = BZ2_bzCompress(&zi->ci.bstream, BZ_RUN);

                zi->ci.pos_in_buffered_data += (uInt)(zi->ci.bstream.total_out_lo32 - uTotalOutBefore_lo);
            }
        }

        if (err == BZ_RUN_OK)
            err = ZIP_OK;
    } else
#endif
    {
        zi->ci.stream.next_in = (Bytef *)buf;
        zi->ci.stream.avail_in = len;

        while ((err == ZIP_OK) && (zi->ci.stream.avail_in > 0)) {
            if (zi->ci.stream.avail_out == 0) {
                if (zip64FlushWriteBuffer(zi) == ZIP_ERRNO)
                    err = ZIP_ERRNO;
                zi->ci.stream.avail_out = (uInt)Z_BUFSIZE;
                zi->ci.stream.next_out = zi->ci.buffered_data;
            }

            if (err != ZIP_OK)
                break;

            if ((zi->ci.compression_method == Z_DEFLATED) && (!zi->ci.raw)) {
                uLong total_out_before = zi->ci.stream.total_out;
                err = deflate(&zi->ci.stream, Z_NO_FLUSH);
                zi->ci.pos_in_buffered_data += (uInt)(zi->ci.stream.total_out - total_out_before);
            } else {
                uInt copy_this, i;
                if (zi->ci.stream.avail_in < zi->ci.stream.avail_out)
                    copy_this = zi->ci.stream.avail_in;
                else
                    copy_this = zi->ci.stream.avail_out;

                for (i = 0; i < copy_this; i++)
                    *(((char *)zi->ci.stream.next_out) + i) =
                        *(((const char *)zi->ci.stream.next_in) + i);

                zi->ci.stream.avail_in -= copy_this;
                zi->ci.stream.avail_out -= copy_this;
                zi->ci.stream.next_in += copy_this;
                zi->ci.stream.next_out += copy_this;
                zi->ci.stream.total_in += copy_this;
                zi->ci.stream.total_out += copy_this;
                zi->ci.pos_in_buffered_data += copy_this;
            }
        }
    }
