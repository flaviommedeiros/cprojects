#ifndef OPENSSL_NO_PSK
if (alg_k & SSL_kPSK) {
        unsigned char *t = NULL;
        unsigned char psk_or_pre_ms[PSK_MAX_PSK_LEN * 2 + 4];
        unsigned int pre_ms_len = 0, psk_len = 0;
        int psk_err = 1;
        char tmp_id[PSK_MAX_IDENTITY_LEN + 1];

        al = SSL_AD_HANDSHAKE_FAILURE;

        n2s(p, i);
        if (n != i + 2) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, SSL_R_LENGTH_MISMATCH);
            goto psk_err;
        }
        if (i > PSK_MAX_IDENTITY_LEN) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            goto psk_err;
        }
        if (s->psk_server_callback == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_PSK_NO_SERVER_CB);
            goto psk_err;
        }

        /*
         * Create guaranteed NULL-terminated identity string for the callback
         */
        memcpy(tmp_id, p, i);
        memset(tmp_id + i, 0, PSK_MAX_IDENTITY_LEN + 1 - i);
        psk_len = s->psk_server_callback(s, tmp_id,
                                         psk_or_pre_ms,
                                         sizeof(psk_or_pre_ms));
        OPENSSL_cleanse(tmp_id, PSK_MAX_IDENTITY_LEN + 1);

        if (psk_len > PSK_MAX_PSK_LEN) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
            goto psk_err;
        } else if (psk_len == 0) {
            /*
             * PSK related to the given identity not found
             */
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_PSK_IDENTITY_NOT_FOUND);
            al = SSL_AD_UNKNOWN_PSK_IDENTITY;
            goto psk_err;
        }

        /* create PSK pre_master_secret */
        pre_ms_len = 2 + psk_len + 2 + psk_len;
        t = psk_or_pre_ms;
        memmove(psk_or_pre_ms + psk_len + 4, psk_or_pre_ms, psk_len);
        s2n(psk_len, t);
        memset(t, 0, psk_len);
        t += psk_len;
        s2n(psk_len, t);

        if (s->session->psk_identity != NULL)
            OPENSSL_free(s->session->psk_identity);
        s->session->psk_identity = BUF_strndup((char *)p, i);
        if (s->session->psk_identity == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto psk_err;
        }

        if (s->session->psk_identity_hint != NULL)
            OPENSSL_free(s->session->psk_identity_hint);
        s->session->psk_identity_hint = BUF_strdup(s->ctx->psk_identity_hint);
        if (s->ctx->psk_identity_hint != NULL &&
            s->session->psk_identity_hint == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto psk_err;
        }

        s->session->master_key_length =
            s->method->ssl3_enc->generate_master_secret(s,
                                                        s->
                                                        session->master_key,
                                                        psk_or_pre_ms,
                                                        pre_ms_len);
        psk_err = 0;
 psk_err:
        OPENSSL_cleanse(psk_or_pre_ms, sizeof(psk_or_pre_ms));
        if (psk_err != 0)
            goto f_err;
    } else
#endif
#ifndef OPENSSL_NO_SRP
    if (alg_k & SSL_kSRP) {
        int param_len;

        n2s(p, i);
        param_len = i + 2;
        if (param_len > n) {
            al = SSL_AD_DECODE_ERROR;
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_BAD_SRP_A_LENGTH);
            goto f_err;
        }
        if (!(s->srp_ctx.A = BN_bin2bn(p, i, NULL))) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        if (BN_ucmp(s->srp_ctx.A, s->srp_ctx.N) >= 0
            || BN_is_zero(s->srp_ctx.A)) {
            al = SSL_AD_ILLEGAL_PARAMETER;
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_BAD_SRP_PARAMETERS);
            goto f_err;
        }
        if (s->session->srp_username != NULL)
            OPENSSL_free(s->session->srp_username);
        s->session->srp_username = BUF_strdup(s->srp_ctx.login);
        if (s->session->srp_username == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        if ((s->session->master_key_length =
             SRP_generate_server_master_secret(s,
                                               s->session->master_key)) < 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
            goto err;
        }

        p += i;
    } else
#endif                          /* OPENSSL_NO_SRP */
    if (alg_k & SSL_kGOST) {
        int ret = 0;
        EVP_PKEY_CTX *pkey_ctx;
        EVP_PKEY *client_pub_pkey = NULL, *pk = NULL;
        unsigned char premaster_secret[32], *start;
        size_t outlen = 32, inlen;
        unsigned long alg_a;
        int Ttag, Tclass;
        long Tlen;

        /* Get our certificate private key */
        alg_a = s->s3->tmp.new_cipher->algorithm_auth;
        if (alg_a & SSL_aGOST94)
            pk = s->cert->pkeys[SSL_PKEY_GOST94].privatekey;
        else if (alg_a & SSL_aGOST01)
            pk = s->cert->pkeys[SSL_PKEY_GOST01].privatekey;

        pkey_ctx = EVP_PKEY_CTX_new(pk, NULL);
        EVP_PKEY_decrypt_init(pkey_ctx);
        /*
         * If client certificate is present and is of the same type, maybe
         * use it for key exchange.  Don't mind errors from
         * EVP_PKEY_derive_set_peer, because it is completely valid to use a
         * client certificate for authorization only.
         */
        client_pub_pkey = X509_get_pubkey(s->session->peer);
        if (client_pub_pkey) {
            if (EVP_PKEY_derive_set_peer(pkey_ctx, client_pub_pkey) <= 0)
                ERR_clear_error();
        }
        /* Decrypt session key */
        if (ASN1_get_object
            ((const unsigned char **)&p, &Tlen, &Ttag, &Tclass,
             n) != V_ASN1_CONSTRUCTED || Ttag != V_ASN1_SEQUENCE
            || Tclass != V_ASN1_UNIVERSAL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DECRYPTION_FAILED);
            goto gerr;
        }
        start = p;
        inlen = Tlen;
        if (EVP_PKEY_decrypt
            (pkey_ctx, premaster_secret, &outlen, start, inlen) <= 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DECRYPTION_FAILED);
            goto gerr;
        }
        /* Generate master secret */
        s->session->master_key_length =
            s->method->ssl3_enc->generate_master_secret(s,
                                                        s->
                                                        session->master_key,
                                                        premaster_secret, 32);
        OPENSSL_cleanse(premaster_secret, sizeof(premaster_secret));
        /* Check if pubkey from client certificate was used */
        if (EVP_PKEY_CTX_ctrl
            (pkey_ctx, -1, -1, EVP_PKEY_CTRL_PEER_KEY, 2, NULL) > 0)
            ret = 2;
        else
            ret = 1;
 gerr:
        EVP_PKEY_free(client_pub_pkey);
        EVP_PKEY_CTX_free(pkey_ctx);
        if (ret)
            return ret;
        else
            goto err;
    } else {
        al = SSL_AD_HANDSHAKE_FAILURE;
        SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, SSL_R_UNKNOWN_CIPHER_TYPE);
        goto f_err;
    }
