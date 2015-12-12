#if defined(MBEDTLS_ZLIB_SUPPORT)
if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
        accept_comp = 0;
    else
#endif
        accept_comp = 1;
