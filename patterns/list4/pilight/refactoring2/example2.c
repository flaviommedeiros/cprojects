#if defined(POLARSSL_SSL_RENEGOTIATION)
if( ssl->renegotiation == SSL_INITIAL_HANDSHAKE )
#endif
    {
        *p++ = (unsigned char)( SSL_EMPTY_RENEGOTIATION_INFO >> 8 );
        *p++ = (unsigned char)( SSL_EMPTY_RENEGOTIATION_INFO      );
        n++;
    }
