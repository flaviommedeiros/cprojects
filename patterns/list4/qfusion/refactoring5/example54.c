#ifndef OPENSSL_NO_RSA
if (pkey->type == EVP_PKEY_RSA) {
                q = md_buf;
                j = 0;
                for (num = 2; num > 0; num--) {
                    EVP_DigestInit_ex(&md_ctx, (num == 2)
                                      ? s->ctx->md5 : s->ctx->sha1, NULL);
                    EVP_DigestUpdate(&md_ctx, &(s->s3->client_random[0]),
                                     SSL3_RANDOM_SIZE);
                    EVP_DigestUpdate(&md_ctx, &(s->s3->server_random[0]),
                                     SSL3_RANDOM_SIZE);
                    EVP_DigestUpdate(&md_ctx, &(d[DTLS1_HM_HEADER_LENGTH]),
                                     n);
                    EVP_DigestFinal_ex(&md_ctx, q, (unsigned int *)&i);
                    q += i;
                    j += i;
                }
                if (RSA_sign(NID_md5_sha1, md_buf, j,
                             &(p[2]), &u, pkey->pkey.rsa) <= 0) {
                    SSLerr(SSL_F_DTLS1_SEND_SERVER_KEY_EXCHANGE, ERR_LIB_RSA);
                    goto err;
                }
                s2n(u, p);
                n += u + 2;
            } else
#endif
#if !defined(OPENSSL_NO_DSA)
            if (pkey->type == EVP_PKEY_DSA) {
                /* lets do DSS */
                EVP_SignInit_ex(&md_ctx, EVP_dss1(), NULL);
                EVP_SignUpdate(&md_ctx, &(s->s3->client_random[0]),
                               SSL3_RANDOM_SIZE);
                EVP_SignUpdate(&md_ctx, &(s->s3->server_random[0]),
                               SSL3_RANDOM_SIZE);
                EVP_SignUpdate(&md_ctx, &(d[DTLS1_HM_HEADER_LENGTH]), n);
                if (!EVP_SignFinal(&md_ctx, &(p[2]),
                                   (unsigned int *)&i, pkey)) {
                    SSLerr(SSL_F_DTLS1_SEND_SERVER_KEY_EXCHANGE, ERR_LIB_DSA);
                    goto err;
                }
                s2n(i, p);
                n += i + 2;
            } else
#endif
#if !defined(OPENSSL_NO_ECDSA)
            if (pkey->type == EVP_PKEY_EC) {
                /* let's do ECDSA */
                EVP_SignInit_ex(&md_ctx, EVP_ecdsa(), NULL);
                EVP_SignUpdate(&md_ctx, &(s->s3->client_random[0]),
                               SSL3_RANDOM_SIZE);
                EVP_SignUpdate(&md_ctx, &(s->s3->server_random[0]),
                               SSL3_RANDOM_SIZE);
                EVP_SignUpdate(&md_ctx, &(d[DTLS1_HM_HEADER_LENGTH]), n);
                if (!EVP_SignFinal(&md_ctx, &(p[2]),
                                   (unsigned int *)&i, pkey)) {
                    SSLerr(SSL_F_DTLS1_SEND_SERVER_KEY_EXCHANGE,
                           ERR_LIB_ECDSA);
                    goto err;
                }
                s2n(i, p);
                n += i + 2;
            } else
#endif
            {
                /* Is this error check actually needed? */
                al = SSL_AD_HANDSHAKE_FAILURE;
                SSLerr(SSL_F_DTLS1_SEND_SERVER_KEY_EXCHANGE,
                       SSL_R_UNKNOWN_PKEY_TYPE);
                goto f_err;
            }
