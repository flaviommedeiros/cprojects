switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
            case cyassl_rc4:
                Arc4Process(ssl->decrypt.arc4, plain, input, sz);
                break;
        #endif

        #ifdef BUILD_DES3
            case cyassl_triple_des:
                return Des3_CbcDecrypt(ssl->decrypt.des3, plain, input, sz);
        #endif

        #ifdef BUILD_AES
            case cyassl_aes:
                return AesCbcDecrypt(ssl->decrypt.aes, plain, input, sz);
        #endif

        #ifdef BUILD_AESGCM
            case cyassl_aes_gcm:
            {
                byte additional[AEAD_AUTH_DATA_SZ];
                byte nonce[AEAD_NONCE_SZ];

                XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                /* sequence number field is 64-bits, we only use 32-bits */
                c32toa(GetSEQIncrement(ssl, 1), additional + AEAD_SEQ_OFFSET);

                #ifdef CYASSL_DTLS
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
                if (AesGcmDecrypt(ssl->decrypt.aes,
                            plain + AEAD_EXP_IV_SZ,
                            input + AEAD_EXP_IV_SZ,
                                sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                            nonce, AEAD_NONCE_SZ,
                            input + sz - ssl->specs.aead_mac_size,
                            ssl->specs.aead_mac_size,
                            additional, AEAD_AUTH_DATA_SZ) < 0) {
                    SendAlert(ssl, alert_fatal, bad_record_mac);
                    XMEMSET(nonce, 0, AEAD_NONCE_SZ);
                    return VERIFY_MAC_ERROR;
                }
                XMEMSET(nonce, 0, AEAD_NONCE_SZ);
            }
            break;
        #endif

        #ifdef HAVE_AESCCM
            case cyassl_aes_ccm:
            {
                byte additional[AEAD_AUTH_DATA_SZ];
                byte nonce[AEAD_NONCE_SZ];

                XMEMSET(additional, 0, AEAD_AUTH_DATA_SZ);

                /* sequence number field is 64-bits, we only use 32-bits */
                c32toa(GetSEQIncrement(ssl, 1), additional + AEAD_SEQ_OFFSET);

                #ifdef CYASSL_DTLS
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
                if (AesCcmDecrypt(ssl->decrypt.aes,
                            plain + AEAD_EXP_IV_SZ,
                            input + AEAD_EXP_IV_SZ,
                                sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                            nonce, AEAD_NONCE_SZ,
                            input + sz - ssl->specs.aead_mac_size,
                            ssl->specs.aead_mac_size,
                            additional, AEAD_AUTH_DATA_SZ) < 0) {
                    SendAlert(ssl, alert_fatal, bad_record_mac);
                    XMEMSET(nonce, 0, AEAD_NONCE_SZ);
                    return VERIFY_MAC_ERROR;
                }
                XMEMSET(nonce, 0, AEAD_NONCE_SZ);
            }
            break;
        #endif

        #ifdef HAVE_CAMELLIA
            case cyassl_camellia:
                CamelliaCbcDecrypt(ssl->decrypt.cam, plain, input, sz);
                break;
        #endif

        #ifdef HAVE_HC128
            case cyassl_hc128:
                return Hc128_Process(ssl->decrypt.hc128, plain, input, sz);
        #endif

        #ifdef BUILD_RABBIT
            case cyassl_rabbit:
                return RabbitProcess(ssl->decrypt.rabbit, plain, input, sz);
        #endif

        #ifdef HAVE_CHACHA
            case cyassl_chacha:
                return ChachaAEADDecrypt(ssl, plain, input, sz);
        #endif

        #ifdef HAVE_NULL_CIPHER
            case cyassl_cipher_null:
                if (input != plain) {
                    XMEMMOVE(plain, input, sz);
                }
                break;
        #endif

            default:
                CYASSL_MSG("CyaSSL Decrypt programming error");
                return DECRYPT_ERROR;
    }
