switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
        case wolfssl_rc4:
            wc_Arc4Process(ssl->decrypt.arc4, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_DES3
        case wolfssl_triple_des:
            ret = wc_Des3_CbcDecrypt(ssl->decrypt.des3, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_AES
        case wolfssl_aes:
            ret = wc_AesCbcDecrypt(ssl->decrypt.aes, output, input, sz);
            break;
        #endif
            
        #ifdef HAVE_HC128
        case wolfssl_hc128:
            wc_Hc128_Process(ssl->decrypt.hc128, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_RABBIT
        case wolfssl_rabbit:
            wc_RabbitProcess(ssl->decrypt.rabbit, output, input, sz);
            break;
        #endif

        #ifdef HAVE_CAMELLIA 
        case wolfssl_camellia:
            wc_CamelliaCbcDecrypt(ssl->decrypt.cam, output, input, sz);
            break;
        #endif

        #ifdef HAVE_IDEA
        case wolfssl_idea:
            wc_IdeaCbcDecrypt(ssl->decrypt.idea, output, input, sz);
            break;
        #endif

        #ifdef HAVE_AESGCM
        case wolfssl_aes_gcm:
            if (sz >= (word32)(AEAD_EXP_IV_SZ + ssl->specs.aead_mac_size))
            {
                byte nonce[AEAD_NONCE_SZ];
                XMEMCPY(nonce, ssl->keys.aead_dec_imp_IV, AEAD_IMP_IV_SZ);
                XMEMCPY(nonce + AEAD_IMP_IV_SZ, input, AEAD_EXP_IV_SZ);

                if (wc_AesGcmEncrypt(ssl->decrypt.aes,
                            output,
                            input + AEAD_EXP_IV_SZ,
                            sz - AEAD_EXP_IV_SZ - ssl->specs.aead_mac_size,
                            nonce, AEAD_NONCE_SZ,
                            NULL, 0,
                            NULL, 0) < 0) {
                    Trace(BAD_DECRYPT);
                    ret = -1;
                }
                ForceZero(nonce, AEAD_NONCE_SZ);
            }
            else {
                Trace(BAD_DECRYPT_SIZE);
                ret = -1;
            }
            break;
         #endif

        default:
            Trace(BAD_DECRYPT_TYPE);
            ret = -1;
            break;
    }
