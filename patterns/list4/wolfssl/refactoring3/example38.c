switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
            case wolfssl_rc4:
                wc_Arc4Process(ssl->encrypt.arc4, out, input, sz);
                break;
        #endif

        #ifdef BUILD_DES3
            case wolfssl_triple_des:
                ret = wc_Des3_CbcEncrypt(ssl->encrypt.des3, out, input, sz);
                break;
        #endif

        #ifdef BUILD_AES
            case wolfssl_aes:
                ret = wc_AesCbcEncrypt(ssl->encrypt.aes, out, input, sz);
                break;
        #endif

        #ifdef BUILD_AESGCM
            case wolfssl_aes_gcm:
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
                    #ifdef WOLFSSL_DTLS
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
                    ret = wc_AesGcmEncrypt(ssl->encrypt.aes,
                                 out + AEAD_EXP_IV_SZ, input + AEAD_EXP_IV_SZ,
                                 sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                 nonce, AEAD_NONCE_SZ,
                                 out + sz - ssl->specs.aead_mac_size,
                                 ssl->specs.aead_mac_size,
                                 additional, AEAD_AUTH_DATA_SZ);
                    AeadIncrementExpIV(ssl);
                    ForceZero(nonce, AEAD_NONCE_SZ);
                }
                break;
        #endif

        #ifdef HAVE_AESCCM
            case wolfssl_aes_ccm:
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
                    #ifdef WOLFSSL_DTLS
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
                    ret = wc_AesCcmEncrypt(ssl->encrypt.aes,
                        out + AEAD_EXP_IV_SZ, input + AEAD_EXP_IV_SZ,
                            sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                        nonce, AEAD_NONCE_SZ,
                        out + sz - ssl->specs.aead_mac_size,
                        ssl->specs.aead_mac_size,
                        additional, AEAD_AUTH_DATA_SZ);
                    AeadIncrementExpIV(ssl);
                    ForceZero(nonce, AEAD_NONCE_SZ);
                }
                break;
        #endif

        #ifdef HAVE_CAMELLIA
            case wolfssl_camellia:
                wc_CamelliaCbcEncrypt(ssl->encrypt.cam, out, input, sz);
                break;
        #endif

        #ifdef HAVE_HC128
            case wolfssl_hc128:
                ret = wc_Hc128_Process(ssl->encrypt.hc128, out, input, sz);
                break;
        #endif

        #ifdef BUILD_RABBIT
            case wolfssl_rabbit:
                ret = wc_RabbitProcess(ssl->encrypt.rabbit, out, input, sz);
                break;
        #endif

        #if defined(HAVE_CHACHA) && defined(HAVE_POLY1305)
            case wolfssl_chacha:
                ret = ChachaAEADEncrypt(ssl, out, input, sz);
                break;
        #endif

        #ifdef HAVE_NULL_CIPHER
            case wolfssl_cipher_null:
                if (input != out) {
                    XMEMMOVE(out, input, sz);
                }
                break;
        #endif

        #ifdef HAVE_IDEA
            case wolfssl_idea:
                ret = wc_IdeaCbcEncrypt(ssl->encrypt.idea, out, input, sz);
                break;
        #endif

            default:
                WOLFSSL_MSG("wolfSSL Encrypt programming error");
                ret = ENCRYPT_ERROR;
    }
