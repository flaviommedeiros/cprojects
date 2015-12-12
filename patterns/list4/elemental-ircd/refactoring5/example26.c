#ifdef HAVE_LIBZ
if(IsZip(conn))
            common_zlib_deflate(conn, inbuf, length);
        else
#endif
            conn_mod_write(conn, inbuf, length);
