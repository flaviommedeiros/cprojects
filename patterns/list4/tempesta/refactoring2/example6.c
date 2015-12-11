#if defined(MBEDTLS_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO)
if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_STREAM )
#endif
        if( ( buf[0] & 0x80 ) != 0 )
            return ssl_parse_client_hello_v2( ssl );
