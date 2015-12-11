#ifndef OPENSSL_NO_RSA
if (type & SSL_kRSA) {
            rsa = cert->rsa_tmp;
            if ((rsa == NULL) && (s->cert->rsa_tmp_cb != NULL)) {
                rsa = s->cert->rsa_tmp_cb(s,
                                          SSL_C_IS_EXPORT(s->s3->
                                                          tmp.new_cipher),
                                          SSL_C_EXPORT_PKEYLENGTH(s->s3->
                                                                  tmp.new_cipher));
                if (rsa == NULL) {
                    al = SSL_AD_HANDSHAKE_FAILURE;
                    SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                           SSL_R_ERROR_GENERATING_TMP_RSA_KEY);
                    goto f_err;
                }
                RSA_up_ref(rsa);
                cert->rsa_tmp = rsa;
            }
            if (rsa == NULL) {
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_MISSING_TMP_RSA_KEY);
                goto f_err;
            }
            r[0] = rsa->n;
            r[1] = rsa->e;
            s->s3->tmp.use_rsa_tmp = 1;
        } else
#endif
#ifndef OPENSSL_NO_DH
        if (type & SSL_kEDH) {
            dhp = cert->dh_tmp;
            if ((dhp == NULL) && (s->cert->dh_tmp_cb != NULL))
                dhp = s->cert->dh_tmp_cb(s,
                                         SSL_C_IS_EXPORT(s->s3->
                                                         tmp.new_cipher),
                                         SSL_C_EXPORT_PKEYLENGTH(s->s3->
                                                                 tmp.new_cipher));
            if (dhp == NULL) {
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_MISSING_TMP_DH_KEY);
                goto f_err;
            }

            if (s->s3->tmp.dh != NULL) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       ERR_R_INTERNAL_ERROR);
                goto err;
            }

            if ((dh = DHparams_dup(dhp)) == NULL) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_DH_LIB);
                goto err;
            }

            s->s3->tmp.dh = dh;
            if ((dhp->pub_key == NULL ||
                 dhp->priv_key == NULL ||
                 (s->options & SSL_OP_SINGLE_DH_USE))) {
                if (!DH_generate_key(dh)) {
                    SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_DH_LIB);
                    goto err;
                }
            } else {
                dh->pub_key = BN_dup(dhp->pub_key);
                dh->priv_key = BN_dup(dhp->priv_key);
                if ((dh->pub_key == NULL) || (dh->priv_key == NULL)) {
                    SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_DH_LIB);
                    goto err;
                }
            }
            r[0] = dh->p;
            r[1] = dh->g;
            r[2] = dh->pub_key;
        } else
#endif
#ifndef OPENSSL_NO_ECDH
        if (type & SSL_kEECDH) {
            const EC_GROUP *group;

            ecdhp = cert->ecdh_tmp;
            if ((ecdhp == NULL) && (s->cert->ecdh_tmp_cb != NULL)) {
                ecdhp = s->cert->ecdh_tmp_cb(s,
                                             SSL_C_IS_EXPORT(s->s3->
                                                             tmp.new_cipher),
                                             SSL_C_EXPORT_PKEYLENGTH(s->
                                                                     s3->tmp.new_cipher));
            }
            if (ecdhp == NULL) {
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_MISSING_TMP_ECDH_KEY);
                goto f_err;
            }

            if (s->s3->tmp.ecdh != NULL) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       ERR_R_INTERNAL_ERROR);
                goto err;
            }

            /* Duplicate the ECDH structure. */
            if (ecdhp == NULL) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_ECDH_LIB);
                goto err;
            }
            if ((ecdh = EC_KEY_dup(ecdhp)) == NULL) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_ECDH_LIB);
                goto err;
            }

            s->s3->tmp.ecdh = ecdh;
            if ((EC_KEY_get0_public_key(ecdh) == NULL) ||
                (EC_KEY_get0_private_key(ecdh) == NULL) ||
                (s->options & SSL_OP_SINGLE_ECDH_USE)) {
                if (!EC_KEY_generate_key(ecdh)) {
                    SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                           ERR_R_ECDH_LIB);
                    goto err;
                }
            }

            if (((group = EC_KEY_get0_group(ecdh)) == NULL) ||
                (EC_KEY_get0_public_key(ecdh) == NULL) ||
                (EC_KEY_get0_private_key(ecdh) == NULL)) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_ECDH_LIB);
                goto err;
            }

            if (SSL_C_IS_EXPORT(s->s3->tmp.new_cipher) &&
                (EC_GROUP_get_degree(group) > 163)) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_ECGROUP_TOO_LARGE_FOR_CIPHER);
                goto err;
            }

            /*
             * XXX: For now, we only support ephemeral ECDH keys over named
             * (not generic) curves. For supported named curves, curve_id is
             * non-zero.
             */
            if ((curve_id =
                 tls1_ec_nid2curve_id(EC_GROUP_get_curve_name(group)))
                == 0) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_UNSUPPORTED_ELLIPTIC_CURVE);
                goto err;
            }

            /*
             * Encode the public key. First check the size of encoding and
             * allocate memory accordingly.
             */
            encodedlen = EC_POINT_point2oct(group,
                                            EC_KEY_get0_public_key(ecdh),
                                            POINT_CONVERSION_UNCOMPRESSED,
                                            NULL, 0, NULL);

            encodedPoint = (unsigned char *)
                OPENSSL_malloc(encodedlen * sizeof(unsigned char));
            bn_ctx = BN_CTX_new();
            if ((encodedPoint == NULL) || (bn_ctx == NULL)) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       ERR_R_MALLOC_FAILURE);
                goto err;
            }

            encodedlen = EC_POINT_point2oct(group,
                                            EC_KEY_get0_public_key(ecdh),
                                            POINT_CONVERSION_UNCOMPRESSED,
                                            encodedPoint, encodedlen, bn_ctx);

            if (encodedlen == 0) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE, ERR_R_ECDH_LIB);
                goto err;
            }

            BN_CTX_free(bn_ctx);
            bn_ctx = NULL;

            /*
             * XXX: For now, we only support named (not generic) curves in
             * ECDH ephemeral key exchanges. In this situation, we need four
             * additional bytes to encode the entire ServerECDHParams
             * structure.
             */
            n = 4 + encodedlen;

            /*
             * We'll generate the serverKeyExchange message explicitly so we
             * can set these to NULLs
             */
            r[0] = NULL;
            r[1] = NULL;
            r[2] = NULL;
            r[3] = NULL;
        } else
#endif                          /* !OPENSSL_NO_ECDH */
#ifndef OPENSSL_NO_PSK
        if (type & SSL_kPSK) {
            /*
             * reserve size for record length and PSK identity hint
             */
            n += 2 + strlen(s->ctx->psk_identity_hint);
        } else
#endif                          /* !OPENSSL_NO_PSK */
#ifndef OPENSSL_NO_SRP
        if (type & SSL_kSRP) {
            if ((s->srp_ctx.N == NULL) ||
                (s->srp_ctx.g == NULL) ||
                (s->srp_ctx.s == NULL) || (s->srp_ctx.B == NULL)) {
                SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_MISSING_SRP_PARAM);
                goto err;
            }
            r[0] = s->srp_ctx.N;
            r[1] = s->srp_ctx.g;
            r[2] = s->srp_ctx.s;
            r[3] = s->srp_ctx.B;
        } else
#endif
        {
            al = SSL_AD_HANDSHAKE_FAILURE;
            SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,
                   SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
            goto f_err;
        }
