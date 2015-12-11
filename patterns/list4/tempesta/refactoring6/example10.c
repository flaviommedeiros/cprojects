if( ssl->handshake->resume == 0 &&
#if defined(MBEDTLS_SSL_RENEGOTIATION)
        ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE &&
#endif
        ssl->session_negotiate->id_len != 0 &&
        ssl->conf->f_get_cache != NULL &&
        ssl->conf->f_get_cache( ssl->conf->p_cache, ssl->session_negotiate ) == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "session successfully restored from cache" ) );
        ssl->handshake->resume = 1;
    }
