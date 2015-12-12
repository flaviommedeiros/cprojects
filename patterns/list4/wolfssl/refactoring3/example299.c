switch (decryptionType) {
#ifndef NO_DES3
        case DES_TYPE:
        {
            Des    dec;
            byte*  desIv = key + 8;

            if (version == PKCS5v2 || version == PKCS12)
                desIv = cbcIv;

            ret = wc_Des_SetKey(&dec, key, desIv, DES_DECRYPTION);
            if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(key, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return ret;
            }

            wc_Des_CbcDecrypt(&dec, input, input, length);
            break;
        }

        case DES3_TYPE:
        {
            Des3   dec;
            byte*  desIv = key + 24;

            if (version == PKCS5v2 || version == PKCS12)
                desIv = cbcIv;
            ret = wc_Des3_SetKey(&dec, key, desIv, DES_DECRYPTION);
            if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(key, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return ret;
            }
            ret = wc_Des3_CbcDecrypt(&dec, input, input, length);
            if (ret != 0) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(key, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return ret;
            }
            break;
        }
#endif
#ifndef NO_RC4
        case RC4_TYPE:
        {
            Arc4    dec;

            wc_Arc4SetKey(&dec, key, derivedLen);
            wc_Arc4Process(&dec, input, input, length);
            break;
        }
#endif

        default:
#ifdef WOLFSSL_SMALL_STACK
            XFREE(key, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
            return ALGO_ID_E;
    }
