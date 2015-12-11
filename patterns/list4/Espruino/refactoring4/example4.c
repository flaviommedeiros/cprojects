#if defined(MBEDTLS_ECP_C)
if( mbedtls_ssl_check_curve( ssl, ssl->handshake->ecdh_ctx.grp.id ) != 0 )
#else
    if( ssl->handshake->ecdh_ctx.grp.nbits < 163 ||
        ssl->handshake->ecdh_ctx.grp.nbits > 521 )
#endif
        return( -1 );
