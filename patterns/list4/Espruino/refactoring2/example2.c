#if defined(MBEDTLS_SSL_RENEGOTIATION)
if( ssl->renego_status == MBEDTLS_SSL_INITIAL_HANDSHAKE )
#endif
    {
        ssl->major_ver = ssl->conf->min_major_ver;
        ssl->minor_ver = ssl->conf->min_minor_ver;
    }
