if( ssl->handshake->resume == 0 || n == 0 ||
#if defined(MBEDTLS_SSL_RENEGOTIATION)
        ssl->renego_status != MBEDTLS_SSL_INITIAL_HANDSHAKE ||
#endif
        ssl->session_negotiate->ciphersuite != i ||
        ssl->session_negotiate->compression != comp ||
        ssl->session_negotiate->id_len != n ||
        memcmp( ssl->session_negotiate->id, buf + 35, n ) != 0 )
    {
        ssl->state++;
        ssl->handshake->resume = 0;
#if defined(MBEDTLS_HAVE_TIME)
        ssl->session_negotiate->start = time( NULL );
#endif
        ssl->session_negotiate->ciphersuite = i;
        ssl->session_negotiate->compression = comp;
        ssl->session_negotiate->id_len = n;
        memcpy( ssl->session_negotiate->id, buf + 35, n );
    }
    else
    {
        ssl->state = MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC;

        if( ( ret = mbedtls_ssl_derive_keys( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_derive_keys", ret );
            return( ret );
        }
    }
