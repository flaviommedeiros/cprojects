switch (handshake_type)
    {
        case HS_CLIENT_HELLO:
            if ((ret = process_client_hello(ssl)) == SSL_OK)
                ret = send_server_hello_sequence(ssl);
            break;

#ifdef CONFIG_SSL_CERT_VERIFICATION
        case HS_CERTIFICATE:/* the client sends its cert */
            ret = process_certificate(ssl, &ssl->x509_ctx);

            if (ret == SSL_OK)    /* verify the cert */
            { 
                int cert_res;
                cert_res = x509_verify(
                        ssl->ssl_ctx->ca_cert_ctx, ssl->x509_ctx);
                ret = (cert_res == 0) ? SSL_OK : SSL_X509_ERROR(cert_res);
            }
            break;

        case HS_CERT_VERIFY:    
            ret = process_cert_verify(ssl);
            add_packet(ssl, buf, hs_len);   /* needs to be done after */
            break;
#endif
        case HS_CLIENT_KEY_XCHG:
            ret = process_client_key_xchg(ssl);
            break;

        case HS_FINISHED:
            ret = process_finished(ssl, hs_len);
            disposable_free(ssl);   /* free up some memory */
            break;
    }
