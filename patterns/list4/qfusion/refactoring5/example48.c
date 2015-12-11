#ifndef OPENSSL_NO_ECDSA
if (pkey->type == EVP_PKEY_EC) {
            if (!ECDSA_sign(pkey->save_type,
                            &(data[MD5_DIGEST_LENGTH]),
                            SHA_DIGEST_LENGTH, &(p[2]),
                            (unsigned int *)&j, pkey->pkey.ec)) {
                SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY, ERR_R_ECDSA_LIB);
                goto err;
            }
            s2n(j, p);
            n = j + 2;
        } else
#endif
        {
            SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY, ERR_R_INTERNAL_ERROR);
            goto err;
        }
