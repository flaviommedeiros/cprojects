#if defined(POLARSSL_SSL_RENEGOTIATION)
if( ssl->renegotiation == SSL_INITIAL_HANDSHAKE )
#endif
    {
        ssl->major_ver = ssl->min_major_ver;
        ssl->minor_ver = ssl->min_minor_ver;
    }
