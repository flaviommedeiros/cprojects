switch (sigOID) {
    #ifndef NO_MD5
        case CTC_MD5wRSA:
        if (Md5Hash(buf, bufSz, digest) == 0) {
            typeH    = MD5h;
            digestSz = MD5_DIGEST_SIZE;
        }
        break;
    #endif
    #if defined(CYASSL_MD2)
        case CTC_MD2wRSA:
        if (Md2Hash(buf, bufSz, digest) == 0) {
            typeH    = MD2h;
            digestSz = MD2_DIGEST_SIZE;
        }
        break;
    #endif
    #ifndef NO_SHA
        case CTC_SHAwRSA:
        case CTC_SHAwDSA:
        case CTC_SHAwECDSA:
        if (ShaHash(buf, bufSz, digest) == 0) {    
            typeH    = SHAh;
            digestSz = SHA_DIGEST_SIZE;                
        }
        break;
    #endif
    #ifndef NO_SHA256
        case CTC_SHA256wRSA:
        case CTC_SHA256wECDSA:
        if (Sha256Hash(buf, bufSz, digest) == 0) {    
            typeH    = SHA256h;
            digestSz = SHA256_DIGEST_SIZE;
        }
        break;
    #endif
    #ifdef CYASSL_SHA512
        case CTC_SHA512wRSA:
        case CTC_SHA512wECDSA:
        if (Sha512Hash(buf, bufSz, digest) == 0) {    
            typeH    = SHA512h;
            digestSz = SHA512_DIGEST_SIZE;
        }
        break;
    #endif
    #ifdef CYASSL_SHA384
        case CTC_SHA384wRSA:
        case CTC_SHA384wECDSA:
        if (Sha384Hash(buf, bufSz, digest) == 0) {    
            typeH    = SHA384h;
            digestSz = SHA384_DIGEST_SIZE;
        }            
        break;
    #endif
        default:
            CYASSL_MSG("Verify Signautre has unsupported type");
    }
