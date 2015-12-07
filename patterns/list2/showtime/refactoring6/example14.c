if( mode == POLARSSL_MODE_STREAM ||
        ( mode == POLARSSL_MODE_CBC
#if defined(POLARSSL_SSL_ENCRYPT_THEN_MAC)
          && ssl->session_out->encrypt_then_mac == SSL_ETM_DISABLED
#endif
        ) )
    {
#if defined(POLARSSL_SSL_PROTO_SSL3)
        if( ssl->minor_ver == SSL_MINOR_VERSION_0 )
        {
            ssl_mac( &ssl->transform_out->md_ctx_enc,
                      ssl->transform_out->mac_enc,
                      ssl->out_msg, ssl->out_msglen,
                      ssl->out_ctr, ssl->out_msgtype );
        }
        else
#endif
#if defined(POLARSSL_SSL_PROTO_TLS1) || defined(POLARSSL_SSL_PROTO_TLS1_1) || \
        defined(POLARSSL_SSL_PROTO_TLS1_2)
        if( ssl->minor_ver >= SSL_MINOR_VERSION_1 )
        {
            md_hmac_update( &ssl->transform_out->md_ctx_enc, ssl->out_ctr, 13 );
            md_hmac_update( &ssl->transform_out->md_ctx_enc,
                             ssl->out_msg, ssl->out_msglen );
            md_hmac_finish( &ssl->transform_out->md_ctx_enc,
                             ssl->out_msg + ssl->out_msglen );
            md_hmac_reset( &ssl->transform_out->md_ctx_enc );
        }
        else
#endif
        {
            SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( POLARSSL_ERR_SSL_INTERNAL_ERROR );
        }

        SSL_DEBUG_BUF( 4, "computed mac",
                       ssl->out_msg + ssl->out_msglen,
                       ssl->transform_out->maclen );

        ssl->out_msglen += ssl->transform_out->maclen;
        auth_done++;
    }
