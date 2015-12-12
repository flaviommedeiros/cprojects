if( suite_info == NULL
#if defined(MBEDTLS_ARC4_C)
            || ( ssl->conf->arc4_disabled &&
                suite_info->cipher == MBEDTLS_CIPHER_ARC4_128 )
#endif
        )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server hello message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO );
    }
