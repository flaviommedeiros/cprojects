#if defined(POLARSSL_SSL_RENEGOTIATION)
if( ssl->renegotiation == SSL_INITIAL_HANDSHAKE )
#endif
    {
        if( ( ret = ssl_fetch_input( ssl, 5 + n ) ) != 0 )
        {
            SSL_DEBUG_RET( 1, "ssl_fetch_input", ret );
            return( ret );
        }
    }
