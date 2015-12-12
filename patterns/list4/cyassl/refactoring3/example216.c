switch (ssl->specs.bulk_cipher_algorithm) {
        #ifdef BUILD_ARC4
        case cyassl_rc4:
            Arc4Process(ssl->decrypt.arc4, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_DES3
        case cyassl_triple_des:
            ret = Des3_CbcDecrypt(ssl->decrypt.des3, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_AES
        case cyassl_aes:
            ret = AesCbcDecrypt(ssl->decrypt.aes, output, input, sz);
            break;
        #endif
            
        #ifdef HAVE_HC128
        case cyassl_hc128:
            Hc128_Process(ssl->decrypt.hc128, output, input, sz);
            break;
        #endif
            
        #ifdef BUILD_RABBIT
        case cyassl_rabbit:
            RabbitProcess(ssl->decrypt.rabbit, output, input, sz);
            break;
        #endif

        #ifdef HAVE_CAMELLIA 
        case cyassl_camellia:
            CamelliaCbcDecrypt(ssl->decrypt.cam, output, input, sz);
            break;
        #endif

        default:
            Trace(BAD_DECRYPT_TYPE);
            ret = -1;
            break;
    }
