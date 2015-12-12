#ifndef NO_RSA
if (ssl->specs.sig_algo == rsa_sa_algo) {
                /* rsa sig size */
                word32 i = 0;
                ret = RsaPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &rsaKey, ssl->buffers.key.length);
                if (ret != 0)
                    goto done_a;
                sigSz = RsaEncryptSize(&rsaKey);
            } else
        #endif

            if (ssl->specs.sig_algo == ecc_dsa_sa_algo) {
                /* ecdsa sig size */
                word32 i = 0;
                ret = EccPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &dsaKey, ssl->buffers.key.length);
                if (ret != 0)
                    goto done_a;
                sigSz = ecc_sig_size(&dsaKey);  /* worst case estimate */
            }
            else {
            #ifndef NO_RSA
                FreeRsaKey(&rsaKey);
            #endif
                ecc_free(&dsaKey);
                ERROR_OUT(ALGO_ID_E, done_a);  /* unsupported type */
            }
