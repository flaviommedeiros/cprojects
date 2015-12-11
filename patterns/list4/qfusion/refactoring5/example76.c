#ifndef OPENSSL_NO_DH
if (alg_k & (SSL_kEDH | SSL_kDHr | SSL_kDHd)) {
        n2s(p, i);
        if (n != i + 2) {
            if (!(s->options & SSL_OP_SSLEAY_080_CLIENT_DH_BUG)) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       SSL_R_DH_PUBLIC_VALUE_LENGTH_IS_WRONG);
                goto err;
            } else {
                p -= 2;
                i = (int)n;
            }
        }

        if (n == 0L) {          /* the parameters are in the cert */
            al = SSL_AD_HANDSHAKE_FAILURE;
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_UNABLE_TO_DECODE_DH_CERTS);
            goto f_err;
        } else {
            if (s->s3->tmp.dh == NULL) {
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       SSL_R_MISSING_TMP_DH_KEY);
                goto f_err;
            } else
                dh_srvr = s->s3->tmp.dh;
        }

        pub = BN_bin2bn(p, i, NULL);
        if (pub == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, SSL_R_BN_LIB);
            goto err;
        }

        i = DH_compute_key(p, pub, dh_srvr);

        if (i <= 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_DH_LIB);
            BN_clear_free(pub);
            goto err;
        }

        DH_free(s->s3->tmp.dh);
        s->s3->tmp.dh = NULL;

        BN_clear_free(pub);
        pub = NULL;
        s->session->master_key_length =
            s->method->ssl3_enc->generate_master_secret(s,
                                                        s->
                                                        session->master_key,
                                                        p, i);
        OPENSSL_cleanse(p, i);
    } else
#endif
#ifndef OPENSSL_NO_KRB5
    if (alg_k & SSL_kKRB5) {
        krb5_error_code krb5rc;
        krb5_data enc_ticket;
        krb5_data authenticator;
        krb5_data enc_pms;
        KSSL_CTX *kssl_ctx = s->kssl_ctx;
        EVP_CIPHER_CTX ciph_ctx;
        const EVP_CIPHER *enc = NULL;
        unsigned char iv[EVP_MAX_IV_LENGTH];
        unsigned char pms[SSL_MAX_MASTER_KEY_LENGTH + EVP_MAX_BLOCK_LENGTH];
        int padl, outl;
        krb5_timestamp authtime = 0;
        krb5_ticket_times ttimes;
        int kerr = 0;

        EVP_CIPHER_CTX_init(&ciph_ctx);

        if (!kssl_ctx)
            kssl_ctx = kssl_ctx_new();

        n2s(p, i);
        enc_ticket.length = i;

        if (n < (long)(enc_ticket.length + 6)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            goto err;
        }

        enc_ticket.data = (char *)p;
        p += enc_ticket.length;

        n2s(p, i);
        authenticator.length = i;

        if (n < (long)(enc_ticket.length + authenticator.length + 6)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            goto err;
        }

        authenticator.data = (char *)p;
        p += authenticator.length;

        n2s(p, i);
        enc_pms.length = i;
        enc_pms.data = (char *)p;
        p += enc_pms.length;

        /*
         * Note that the length is checked again below, ** after decryption
         */
        if (enc_pms.length > sizeof pms) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            goto err;
        }

        if (n != (long)(enc_ticket.length + authenticator.length +
                        enc_pms.length + 6)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            goto err;
        }

        if ((krb5rc = kssl_sget_tkt(kssl_ctx, &enc_ticket, &ttimes,
                                    &kssl_err)) != 0) {
# ifdef KSSL_DEBUG
            fprintf(stderr, "kssl_sget_tkt rtn %d [%d]\n",
                    krb5rc, kssl_err.reason);
            if (kssl_err.text)
                fprintf(stderr, "kssl_err text= %s\n", kssl_err.text);
# endif                         /* KSSL_DEBUG */
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, kssl_err.reason);
            goto err;
        }

        /*
         * Note: no authenticator is not considered an error, ** but will
         * return authtime == 0.
         */
        if ((krb5rc = kssl_check_authent(kssl_ctx, &authenticator,
                                         &authtime, &kssl_err)) != 0) {
# ifdef KSSL_DEBUG
            fprintf(stderr, "kssl_check_authent rtn %d [%d]\n",
                    krb5rc, kssl_err.reason);
            if (kssl_err.text)
                fprintf(stderr, "kssl_err text= %s\n", kssl_err.text);
# endif                         /* KSSL_DEBUG */
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, kssl_err.reason);
            goto err;
        }

        if ((krb5rc = kssl_validate_times(authtime, &ttimes)) != 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, krb5rc);
            goto err;
        }
# ifdef KSSL_DEBUG
        kssl_ctx_show(kssl_ctx);
# endif                         /* KSSL_DEBUG */

        enc = kssl_map_enc(kssl_ctx->enctype);
        if (enc == NULL)
            goto err;

        memset(iv, 0, sizeof iv); /* per RFC 1510 */

        if (!EVP_DecryptInit_ex(&ciph_ctx, enc, NULL, kssl_ctx->key, iv)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DECRYPTION_FAILED);
            goto err;
        }
        if (!EVP_DecryptUpdate(&ciph_ctx, pms, &outl,
                               (unsigned char *)enc_pms.data, enc_pms.length))
        {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DECRYPTION_FAILED);
            kerr = 1;
            goto kclean;
        }
        if (outl > SSL_MAX_MASTER_KEY_LENGTH) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            kerr = 1;
            goto kclean;
        }
        if (!EVP_DecryptFinal_ex(&ciph_ctx, &(pms[outl]), &padl)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DECRYPTION_FAILED);
            kerr = 1;
            goto kclean;
        }
        outl += padl;
        if (outl > SSL_MAX_MASTER_KEY_LENGTH) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                   SSL_R_DATA_LENGTH_TOO_LONG);
            kerr = 1;
            goto kclean;
        }
        if (!((pms[0] == (s->client_version >> 8))
              && (pms[1] == (s->client_version & 0xff)))) {
            /*
             * The premaster secret must contain the same version number as
             * the ClientHello to detect version rollback attacks (strangely,
             * the protocol does not offer such protection for DH
             * ciphersuites). However, buggy clients exist that send random
             * bytes instead of the protocol version. If
             * SSL_OP_TLS_ROLLBACK_BUG is set, tolerate such clients.
             * (Perhaps we should have a separate BUG value for the Kerberos
             * cipher)
             */
            if (!(s->options & SSL_OP_TLS_ROLLBACK_BUG)) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       SSL_AD_DECODE_ERROR);
                kerr = 1;
                goto kclean;
            }
        }

        EVP_CIPHER_CTX_cleanup(&ciph_ctx);

        s->session->master_key_length =
            s->method->ssl3_enc->generate_master_secret(s,
                                                        s->
                                                        session->master_key,
                                                        pms, outl);

        if (kssl_ctx->client_princ) {
            size_t len = strlen(kssl_ctx->client_princ);
            if (len < SSL_MAX_KRB5_PRINCIPAL_LENGTH) {
                s->session->krb5_client_princ_len = len;
                memcpy(s->session->krb5_client_princ, kssl_ctx->client_princ,
                       len);
            }
        }

        /*- Was doing kssl_ctx_free() here,
         *  but it caused problems for apache.
         *  kssl_ctx = kssl_ctx_free(kssl_ctx);
         *  if (s->kssl_ctx)  s->kssl_ctx = NULL;
         */

 kclean:
        OPENSSL_cleanse(pms, sizeof(pms));
        if (kerr)
            goto err;
    } else
#endif                          /* OPENSSL_NO_KRB5 */

#ifndef OPENSSL_NO_ECDH
    if (alg_k & (SSL_kEECDH | SSL_kECDHr | SSL_kECDHe)) {
        int ret = 1;
        int field_size = 0;
        const EC_KEY *tkey;
        const EC_GROUP *group;
        const BIGNUM *priv_key;

        /* initialize structures for server's ECDH key pair */
        if ((srvr_ecdh = EC_KEY_new()) == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        /* Let's get server private key and group information */
        if (alg_k & (SSL_kECDHr | SSL_kECDHe)) {
            /* use the certificate */
            tkey = s->cert->pkeys[SSL_PKEY_ECC].privatekey->pkey.ec;
        } else {
            /*
             * use the ephermeral values we saved when generating the
             * ServerKeyExchange msg.
             */
            tkey = s->s3->tmp.ecdh;
        }

        group = EC_KEY_get0_group(tkey);
        priv_key = EC_KEY_get0_private_key(tkey);

        if (!EC_KEY_set_group(srvr_ecdh, group) ||
            !EC_KEY_set_private_key(srvr_ecdh, priv_key)) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_EC_LIB);
            goto err;
        }

        /* Let's get client's public key */
        if ((clnt_ecpoint = EC_POINT_new(group)) == NULL) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        if (n == 0L) {
            /* Client Publickey was in Client Certificate */

            if (alg_k & SSL_kEECDH) {
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       SSL_R_MISSING_TMP_ECDH_KEY);
                goto f_err;
            }
            if (((clnt_pub_pkey = X509_get_pubkey(s->session->peer))
                 == NULL) || (clnt_pub_pkey->type != EVP_PKEY_EC)) {
                /*
                 * XXX: For now, we do not support client authentication
                 * using ECDH certificates so this branch (n == 0L) of the
                 * code is never executed. When that support is added, we
                 * ought to ensure the key received in the certificate is
                 * authorized for key agreement. ECDH_compute_key implicitly
                 * checks that the two ECDH shares are for the same group.
                 */
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       SSL_R_UNABLE_TO_DECODE_ECDH_CERTS);
                goto f_err;
            }

            if (EC_POINT_copy(clnt_ecpoint,
                              EC_KEY_get0_public_key(clnt_pub_pkey->
                                                     pkey.ec)) == 0) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_EC_LIB);
                goto err;
            }
            ret = 2;            /* Skip certificate verify processing */
        } else {
            /*
             * Get client's public key from encoded point in the
             * ClientKeyExchange message.
             */
            if ((bn_ctx = BN_CTX_new()) == NULL) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE,
                       ERR_R_MALLOC_FAILURE);
                goto err;
            }

            /* Get encoded point length */
            i = *p;
            p += 1;
            if (n != 1 + i) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_EC_LIB);
                goto err;
            }
            if (EC_POINT_oct2point(group, clnt_ecpoint, p, i, bn_ctx) == 0) {
                SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_EC_LIB);
                goto err;
            }
            /*
             * p is pointing to somewhere in the buffer currently, so set it
             * to the start
             */
            p = (unsigned char *)s->init_buf->data;
        }

        /* Compute the shared pre-master secret */
        field_size = EC_GROUP_get_degree(group);
        if (field_size <= 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_ECDH_LIB);
            goto err;
        }
        i = ECDH_compute_key(p, (field_size + 7) / 8, clnt_ecpoint, srvr_ecdh,
                             NULL);
        if (i <= 0) {
            SSLerr(SSL_F_SSL3_GET_CLIENT_KEY_EXCHANGE, ERR_R_ECDH_LIB);
            goto err;
        }

        EVP_PKEY_free(clnt_pub_pkey);
        EC_POINT_free(clnt_ecpoint);
        EC_KEY_free(srvr_ecdh);
        BN_CTX_free(bn_ctx);
        EC_KEY_free(s->s3->tmp.ecdh);
        s->s3->tmp.ecdh = NULL;

        /* Compute the master secret */
        s->session->master_key_length =
            s->method->ssl3_enc->generate_master_secret(s,
                                                        s->
                                                        session->master_key,
                                                        p, i);

        OPENSSL_cleanse(p, i);
        return (ret);
    } else
#endif
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
