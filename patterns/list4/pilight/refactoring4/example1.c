#if defined(POLARSSL_SSL_ECP_SET_CURVES)
if( ! ssl_curve_is_acceptable( ssl, ssl->handshake->ecdh_ctx.grp.id ) )
#else
    if( ssl->handshake->ecdh_ctx.grp.nbits < 163 ||
        ssl->handshake->ecdh_ctx.grp.nbits > 521 )
#endif
        return( -1 );
