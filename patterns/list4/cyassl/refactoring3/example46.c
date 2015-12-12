switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
            case cyassl_rc4:
                Arc4Process(ssl->encrypt.arc4, out, input, sz);
                break;
        #endif

        #ifdef BUILD_DES3
            case cyassl_triple_des:
                return Des3_CbcEncrypt(ssl->encrypt.des3, out, input, sz);
        #endif

        #ifdef BUILD_AES
            case cyassl_aes:
                return AesCbcEncrypt(ssl->encrypt.aes, out, input, sz);
        #endif

        #ifdef BUILD_AESGCM
            case cyassl_aes_gcm:
                {
                    int  gcmRet;
                    byte additional[AEAD_AUTH_DATA_SZ];
                    byte nonce[AEAD_NONCE_SZ];
                    const byte* additionalSrc = input - 5;

                    XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                    /* sequence number field is 64-bits, we only use 32-bits */
                    c32toa(GetSEQIncrement(ssl, 0),
                                            additional + AEAD_SEQ_OFFSET);

                    /* Store the type, version. Unfortunately, they are in
                     * the input buffer ahead of the plaintext. */
                    #ifdef CYASSL_DTLS
                        if (ssl->options.dtls) {
                            c16toa(ssl->keys.dtls_epoch, additional);
                            additionalSrc -= DTLS_HANDSHAKE_EXTRA;
                        }
                    #endif
                    XMEMCPY(additional + AEAD_TYPE_OFFSET, additionalSrc, 3);

                    /* Store the length of the plain text minus the explicit
                     * IV length minus the authentication tag size. */
                    c16toa(sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                                additional + AEAD_LEN_OFFSET);
                    XMEMCPY(nonce,
                                 ssl->keys.aead_enc_imp_IV, AEAD_IMP_IV_SZ);
                    XMEMCPY(nonce + AEAD_IMP_IV_SZ,
                                     ssl->keys.aead_exp_IV, AEAD_EXP_IV_SZ);
                    gcmRet = AesGcmEncrypt(ssl->encrypt.aes,
                                 out + AEAD_EXP_IV_SZ, input + AEAD_EXP_IV_SZ,
                                 sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                 nonce, AEAD_NONCE_SZ,
                                 out + sz - ssl->specs.aead_mac_size,
                                 ssl->specs.aead_mac_size,
                                 additional, AEAD_AUTH_DATA_SZ);
                    if (gcmRet == 0)
                        AeadIncrementExpIV(ssl);
                    XMEMSET(nonce, 0, AEAD_NONCE_SZ);
                    return gcmRet;
                }
                break;
        #endif

        #ifdef HAVE_AESCCM
            case cyassl_aes_ccm:
                {
                    byte additional[AEAD_AUTH_DATA_SZ];
                    byte nonce[AEAD_NONCE_SZ];
                    const byte* additionalSrc = input - 5;

                    XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                    /* sequence number field is 64-bits, we only use 32-bits */
                    c32toa(GetSEQIncrement(ssl, 0),
                                            additional + AEAD_SEQ_OFFSET);

                    /* Store the type, version. Unfortunately, they are in
                     * the input buffer ahead of the plaintext. */
                    #ifdef CYASSL_DTLS
                        if (ssl->options.dtls) {
                            c16toa(ssl->keys.dtls_epoch, additional);
                            additionalSrc -= DTLS_HANDSHAKE_EXTRA;
                        }
                    #endif
                    XMEMCPY(additional + AEAD_TYPE_OFFSET, additionalSrc, 3);

                    /* Store the length of the plain text minus the explicit
                     * IV length minus the authentication tag size. */
                    c16toa(sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                                additional + AEAD_LEN_OFFSET);
                    XMEMCPY(nonce,
                                 ssl->keys.aead_enc_imp_IV, AEAD_IMP_IV_SZ);
                    XMEMCPY(nonce + AEAD_IMP_IV_SZ,
                                     ssl->keys.aead_exp_IV, AEAD_EXP_IV_SZ);
                    AesCcmEncrypt(ssl->encrypt.aes,
                        out + AEAD_EXP_IV_SZ, input + AEAD_EXP_IV_SZ,
                            sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                        nonce, AEAD_NONCE_SZ,
                        out + sz - ssl->specs.aead_mac_size,
                        ssl->specs.aead_mac_size,
                        additional, AEAD_AUTH_DATA_SZ);
                    AeadIncrementExpIV(ssl);
                    XMEMSET(nonce, 0, AEAD_NONCE_SZ);
                }
                break;
        #endif

        #ifdef HAVE_CAMELLIA
            case cyassl_camellia:
                CamelliaCbcEncrypt(ssl->encrypt.cam, out, input, sz);
                break;
        #endif

        #ifdef HAVE_HC128
            case cyassl_hc128:
                return Hc128_Process(ssl->encrypt.hc128, out, input, sz);
        #endif

        #ifdef BUILD_RABBIT
            case cyassl_rabbit:
                return RabbitProcess(ssl->encrypt.rabbit, out, input, sz);
        #endif

        #ifdef HAVE_CHACHA
            case cyassl_chacha:
                return ChachaAEADEncrypt(ssl, out, input, sz);
        #endif

        #ifdef HAVE_NULL_CIPHER
            case cyassl_cipher_null:
                if (input != out) {
                    XMEMMOVE(out, input, sz);
                }
                break;
        #endif

            default:
                CYASSL_MSG("CyaSSL Encrypt programming error");
                return ENCRYPT_ERROR;
    }
