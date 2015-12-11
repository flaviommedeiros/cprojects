#if defined(MBEDTLS_SSL_PROTO_DTLS)
if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
            ( ciphersuite_info->flags & MBEDTLS_CIPHERSUITE_NODTLS ) )
            continue;
