switch (cmd) {
#ifndef OPENSSL_NO_RSA
    case SSL_CTRL_NEED_TMP_RSA:
        if ((cert->rsa_tmp == NULL) &&
            ((cert->pkeys[SSL_PKEY_RSA_ENC].privatekey == NULL) ||
             (EVP_PKEY_size(cert->pkeys[SSL_PKEY_RSA_ENC].privatekey) >
              (512 / 8)))
            )
            return (1);
        else
            return (0);
        /* break; */
    case SSL_CTRL_SET_TMP_RSA:
        {
            RSA *rsa;
            int i;

            rsa = (RSA *)parg;
            i = 1;
            if (rsa == NULL)
                i = 0;
            else {
                if ((rsa = RSAPrivateKey_dup(rsa)) == NULL)
                    i = 0;
            }
            if (!i) {
                SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_RSA_LIB);
                return (0);
            } else {
                if (cert->rsa_tmp != NULL)
                    RSA_free(cert->rsa_tmp);
                cert->rsa_tmp = rsa;
                return (1);
            }
        }
        /* break; */
    case SSL_CTRL_SET_TMP_RSA_CB:
        {
            SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
            return (0);
        }
        break;
#endif
#ifndef OPENSSL_NO_DH
    case SSL_CTRL_SET_TMP_DH:
        {
            DH *new = NULL, *dh;

            dh = (DH *)parg;
            if ((new = DHparams_dup(dh)) == NULL) {
                SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_DH_LIB);
                return 0;
            }
            if (!(ctx->options & SSL_OP_SINGLE_DH_USE)) {
                if (!DH_generate_key(new)) {
                    SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_DH_LIB);
                    DH_free(new);
                    return 0;
                }
            }
            if (cert->dh_tmp != NULL)
                DH_free(cert->dh_tmp);
            cert->dh_tmp = new;
            return 1;
        }
        /*
         * break;
         */
    case SSL_CTRL_SET_TMP_DH_CB:
        {
            SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
            return (0);
        }
        break;
#endif
#ifndef OPENSSL_NO_ECDH
    case SSL_CTRL_SET_TMP_ECDH:
        {
            EC_KEY *ecdh = NULL;

            if (parg == NULL) {
                SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_ECDH_LIB);
                return 0;
            }
            ecdh = EC_KEY_dup((EC_KEY *)parg);
            if (ecdh == NULL) {
                SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_EC_LIB);
                return 0;
            }
            if (!(ctx->options & SSL_OP_SINGLE_ECDH_USE)) {
                if (!EC_KEY_generate_key(ecdh)) {
                    EC_KEY_free(ecdh);
                    SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_ECDH_LIB);
                    return 0;
                }
            }

            if (cert->ecdh_tmp != NULL) {
                EC_KEY_free(cert->ecdh_tmp);
            }
            cert->ecdh_tmp = ecdh;
            return 1;
        }
        /* break; */
    case SSL_CTRL_SET_TMP_ECDH_CB:
        {
            SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
            return (0);
        }
        break;
#endif                          /* !OPENSSL_NO_ECDH */
#ifndef OPENSSL_NO_TLSEXT
    case SSL_CTRL_SET_TLSEXT_SERVERNAME_ARG:
        ctx->tlsext_servername_arg = parg;
        break;
    case SSL_CTRL_SET_TLSEXT_TICKET_KEYS:
    case SSL_CTRL_GET_TLSEXT_TICKET_KEYS:
        {
            unsigned char *keys = parg;
            if (!keys)
                return 48;
            if (larg != 48) {
                SSLerr(SSL_F_SSL3_CTX_CTRL, SSL_R_INVALID_TICKET_KEYS_LENGTH);
                return 0;
            }
            if (cmd == SSL_CTRL_SET_TLSEXT_TICKET_KEYS) {
                memcpy(ctx->tlsext_tick_key_name, keys, 16);
                memcpy(ctx->tlsext_tick_hmac_key, keys + 16, 16);
                memcpy(ctx->tlsext_tick_aes_key, keys + 32, 16);
            } else {
                memcpy(keys, ctx->tlsext_tick_key_name, 16);
                memcpy(keys + 16, ctx->tlsext_tick_hmac_key, 16);
                memcpy(keys + 32, ctx->tlsext_tick_aes_key, 16);
            }
            return 1;
        }

# ifdef TLSEXT_TYPE_opaque_prf_input
    case SSL_CTRL_SET_TLSEXT_OPAQUE_PRF_INPUT_CB_ARG:
        ctx->tlsext_opaque_prf_input_callback_arg = parg;
        return 1;
# endif

    case SSL_CTRL_SET_TLSEXT_STATUS_REQ_CB_ARG:
        ctx->tlsext_status_arg = parg;
        return 1;
        break;

# ifndef OPENSSL_NO_SRP
    case SSL_CTRL_SET_TLS_EXT_SRP_USERNAME:
        ctx->srp_ctx.srp_Mask |= SSL_kSRP;
        if (ctx->srp_ctx.login != NULL)
            OPENSSL_free(ctx->srp_ctx.login);
        ctx->srp_ctx.login = NULL;
        if (parg == NULL)
            break;
        if (strlen((const char *)parg) > 255
            || strlen((const char *)parg) < 1) {
            SSLerr(SSL_F_SSL3_CTX_CTRL, SSL_R_INVALID_SRP_USERNAME);
            return 0;
        }
        if ((ctx->srp_ctx.login = BUF_strdup((char *)parg)) == NULL) {
            SSLerr(SSL_F_SSL3_CTX_CTRL, ERR_R_INTERNAL_ERROR);
            return 0;
        }
        break;
    case SSL_CTRL_SET_TLS_EXT_SRP_PASSWORD:
        ctx->srp_ctx.SRP_give_srp_client_pwd_callback =
            srp_password_from_info_cb;
        ctx->srp_ctx.info = parg;
        break;
    case SSL_CTRL_SET_SRP_ARG:
        ctx->srp_ctx.srp_Mask |= SSL_kSRP;
        ctx->srp_ctx.SRP_cb_arg = parg;
        break;

    case SSL_CTRL_SET_TLS_EXT_SRP_STRENGTH:
        ctx->srp_ctx.strength = larg;
        break;
# endif
#endif                          /* !OPENSSL_NO_TLSEXT */

        /* A Thawte special :-) */
    case SSL_CTRL_EXTRA_CHAIN_CERT:
        if (ctx->extra_certs == NULL) {
            if ((ctx->extra_certs = sk_X509_new_null()) == NULL)
                return (0);
        }
        sk_X509_push(ctx->extra_certs, (X509 *)parg);
        break;

    case SSL_CTRL_GET_EXTRA_CHAIN_CERTS:
        *(STACK_OF(X509) **)parg = ctx->extra_certs;
        break;

    case SSL_CTRL_CLEAR_EXTRA_CHAIN_CERTS:
        if (ctx->extra_certs) {
            sk_X509_pop_free(ctx->extra_certs, X509_free);
            ctx->extra_certs = NULL;
        }
        break;

    default:
        return (0);
    }
