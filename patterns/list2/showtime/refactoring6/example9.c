if( ssl->handshake->resume == 0 &&
#if defined(POLARSSL_SSL_RENEGOTIATION)
        ssl->renegotiation == SSL_INITIAL_HANDSHAKE &&
#endif
        ssl->session_negotiate->length != 0 &&
        ssl->f_get_cache != NULL &&
        ssl->f_get_cache( ssl->p_get_cache, ssl->session_negotiate ) == 0 )
    {
        SSL_DEBUG_MSG( 3, ( "session successfully restored from cache" ) );
        ssl->handshake->resume = 1;
    }
