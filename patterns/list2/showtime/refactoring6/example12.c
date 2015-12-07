if( comp != SSL_COMPRESS_NULL
#if defined(POLARSSL_ZLIB_SUPPORT)
        && comp != SSL_COMPRESS_DEFLATE
#endif
      )
    {
        SSL_DEBUG_MSG( 1, ( "bad server hello message" ) );
        return( POLARSSL_ERR_SSL_BAD_HS_SERVER_HELLO );
    }
