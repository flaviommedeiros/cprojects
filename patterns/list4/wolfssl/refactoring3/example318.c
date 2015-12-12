switch (sigAlgoType) {
    #ifndef NO_MD5
        case CTC_MD5wRSA:
        if ((ret = wc_Md5Hash(buffer, sz, digest)) == 0) {
            typeH    = MD5h;
            digestSz = MD5_DIGEST_SIZE;
        }
        break;
    #endif
    #ifndef NO_SHA
        case CTC_SHAwRSA:
        case CTC_SHAwECDSA:
        if ((ret = wc_ShaHash(buffer, sz, digest)) == 0) {
            typeH    = SHAh;
            digestSz = SHA_DIGEST_SIZE;
        }
        break;
    #endif
    #ifndef NO_SHA256
        case CTC_SHA256wRSA:
        case CTC_SHA256wECDSA:
        if ((ret = wc_Sha256Hash(buffer, sz, digest)) == 0) {
            typeH    = SHA256h;
            digestSz = SHA256_DIGEST_SIZE;
        }
        break;
    #endif
    #ifdef WOLFSSL_SHA512
        case CTC_SHA512wRSA:
        case CTC_SHA512wECDSA:
        if ((ret = wc_Sha512Hash(buffer, sz, digest)) == 0) {
            typeH    = SHA256h;
            digestSz = SHA256_DIGEST_SIZE;
        }
        break;
    #endif
        default:
            WOLFSSL_MSG("MakeSignautre called with unsupported type");
            ret = ALGO_ID_E;
    }
