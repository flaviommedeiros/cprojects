#if !defined(MBEDTLS_X509_ALLOW_EXTENSIONS_NON_V3)
if( crt->version == 3 )
#endif
    {
        ret = x509_get_crt_ext( &p, end, crt );
        if( ret != 0 )
        {
            mbedtls_x509_crt_free( crt );
            return( ret );
        }
    }
