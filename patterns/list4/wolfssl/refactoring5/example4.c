#ifndef NO_RSA
if (ssl->specs.sig_algo == rsa_sa_algo) {
                /* rsa sig size */
                word32 i = 0;
                ret = wc_RsaPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &rsaKey, ssl->buffers.key.length);
                if (ret != 0) {
                    goto done_a;
                }
                sigSz = wc_RsaEncryptSize(&rsaKey);
            } else
        #endif

            if (ssl->specs.sig_algo == ecc_dsa_sa_algo) {
                /* ecdsa sig size */
                word32 i = 0;
                ret = wc_EccPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &dsaKey, ssl->buffers.key.length);
                if (ret != 0) {
                    goto done_a;
                }
                sigSz = wc_ecc_sig_size(&dsaKey);  /* worst case estimate */
            }
            else {
            #ifndef NO_RSA
                wc_FreeRsaKey(&rsaKey);
            #endif
                wc_ecc_free(&dsaKey);
                ERROR_OUT(ALGO_ID_E, done_a);  /* unsupported type */
            }
