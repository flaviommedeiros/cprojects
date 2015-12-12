if( n < 16 || n > 32 ||
#if defined(POLARSSL_SSL_RENEGOTIATION)
        ssl->renegotiation != SSL_INITIAL_HANDSHAKE ||
#endif
        ssl->handshake->resume == 0 )
    {
        n = 0;
    }
