switch (sigAlgoType) {
    #ifndef NO_MD5
        case CTC_MD5wRSA:
        if ((ret = Md5Hash(buffer, sz, digest)) == 0) {
            typeH    = MD5h;
            digestSz = MD5_DIGEST_SIZE;
        }
        break;
    #endif
    #ifndef NO_SHA
        case CTC_SHAwRSA:
        case CTC_SHAwECDSA:
        if ((ret = ShaHash(buffer, sz, digest)) == 0) {
            typeH    = SHAh;
            digestSz = SHA_DIGEST_SIZE;          
        }
        break;
    #endif
    #ifndef NO_SHA256
        case CTC_SHA256wRSA:
        case CTC_SHA256wECDSA:
        if ((ret = Sha256Hash(buffer, sz, digest)) == 0) {
            typeH    = SHA256h;
            digestSz = SHA256_DIGEST_SIZE;
        }
        break;
    #endif
        default:
            CYASSL_MSG("MakeSignautre called with unsupported type");
            ret = ALGO_ID_E;
    }
