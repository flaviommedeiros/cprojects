switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
            case wolfssl_rc4:
                wc_Arc4Process(ssl->decrypt.arc4, plain, input, sz);
                break;
        #endif

        #ifdef BUILD_DES3
            case wolfssl_triple_des:
                ret = wc_Des3_CbcDecrypt(ssl->decrypt.des3, plain, input, sz);
                break;
        #endif

        #ifdef BUILD_AES
            case wolfssl_aes:
                ret = wc_AesCbcDecrypt(ssl->decrypt.aes, plain, input, sz);
                break;
        #endif

        #ifdef BUILD_AESGCM
            case wolfssl_aes_gcm:
            {
                byte additional[AEAD_AUTH_DATA_SZ];
                byte nonce[AEAD_NONCE_SZ];

                XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                /* sequence number field is 64-bits, we only use 32-bits */
                c32toa(GetSEQIncrement(ssl, 1), additional + AEAD_SEQ_OFFSET);

                #ifdef WOLFSSL_DTLS
                    if (ssl->options.dtls)
                        c16toa(ssl->keys.dtls_state.curEpoch, additional);
                #endif

                additional[AEAD_TYPE_OFFSET] = ssl->curRL.type;
                additional[AEAD_VMAJ_OFFSET] = ssl->curRL.pvMajor;
                additional[AEAD_VMIN_OFFSET] = ssl->curRL.pvMinor;

                c16toa(sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                        additional + AEAD_LEN_OFFSET);
                XMEMCPY(nonce, ssl->keys.aead_dec_imp_IV, AEAD_IMP_IV_SZ);
                XMEMCPY(nonce + AEAD_IMP_IV_SZ, input, AEAD_EXP_IV_SZ);
                if (wc_AesGcmDecrypt(ssl->decrypt.aes,
                            plain + AEAD_EXP_IV_SZ,
                            input + AEAD_EXP_IV_SZ,
                                sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                            nonce, AEAD_NONCE_SZ,
                            input + sz - ssl->specs.aead_mac_size,
                            ssl->specs.aead_mac_size,
                            additional, AEAD_AUTH_DATA_SZ) < 0) {
                    SendAlert(ssl, alert_fatal, bad_record_mac);
                    ret = VERIFY_MAC_ERROR;
                }
                ForceZero(nonce, AEAD_NONCE_SZ);
            }
            break;
        #endif

        #ifdef HAVE_AESCCM
            case wolfssl_aes_ccm:
            {
                byte additional[AEAD_AUTH_DATA_SZ];
                byte nonce[AEAD_NONCE_SZ];

                XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                /* sequence number field is 64-bits, we only use 32-bits */
                c32toa(GetSEQIncrement(ssl, 1), additional + AEAD_SEQ_OFFSET);

                #ifdef WOLFSSL_DTLS
                    if (ssl->options.dtls)
                        c16toa(ssl->keys.dtls_state.curEpoch, additional);
                #endif

                additional[AEAD_TYPE_OFFSET] = ssl->curRL.type;
                additional[AEAD_VMAJ_OFFSET] = ssl->curRL.pvMajor;
                additional[AEAD_VMIN_OFFSET] = ssl->curRL.pvMinor;

                c16toa(sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                                        additional + AEAD_LEN_OFFSET);
                XMEMCPY(nonce, ssl->keys.aead_dec_imp_IV, AEAD_IMP_IV_SZ);
                XMEMCPY(nonce + AEAD_IMP_IV_SZ, input, AEAD_EXP_IV_SZ);
                if (wc_AesCcmDecrypt(ssl->decrypt.aes,
                            plain + AEAD_EXP_IV_SZ,
                            input + AEAD_EXP_IV_SZ,
                                sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                            nonce, AEAD_NONCE_SZ,
                            input + sz - ssl->specs.aead_mac_size,
                            ssl->specs.aead_mac_size,
                            additional, AEAD_AUTH_DATA_SZ) < 0) {
                    SendAlert(ssl, alert_fatal, bad_record_mac);
                    ret = VERIFY_MAC_ERROR;
                }
                ForceZero(nonce, AEAD_NONCE_SZ);
            }
            break;
        #endif

        #ifdef HAVE_CAMELLIA
            case wolfssl_camellia:
                wc_CamelliaCbcDecrypt(ssl->decrypt.cam, plain, input, sz);
                break;
        #endif

        #ifdef HAVE_HC128
            case wolfssl_hc128:
                ret = wc_Hc128_Process(ssl->decrypt.hc128, plain, input, sz);
                break;
        #endif

        #ifdef BUILD_RABBIT
            case wolfssl_rabbit:
                ret = wc_RabbitProcess(ssl->decrypt.rabbit, plain, input, sz);
                break;
        #endif

        #if defined(HAVE_CHACHA) && defined(HAVE_POLY1305)
            case wolfssl_chacha:
                ret = ChachaAEADDecrypt(ssl, plain, input, sz);
                break;
        #endif

        #ifdef HAVE_NULL_CIPHER
            case wolfssl_cipher_null:
                if (input != plain) {
                    XMEMMOVE(plain, input, sz);
                }
                break;
        #endif

        #ifdef HAVE_IDEA
            case wolfssl_idea:
                ret = wc_IdeaCbcDecrypt(ssl->decrypt.idea, plain, input, sz);
                break;
        #endif

            default:
                WOLFSSL_MSG("wolfSSL Decrypt programming error");
                ret = DECRYPT_ERROR;
    }
