#ifdef HAVE_LIBZ
if(IsZip(conn))
            common_zlib_inflate(conn, inbuf, length);
        else
#endif
            conn_plain_write(conn, inbuf, length);
