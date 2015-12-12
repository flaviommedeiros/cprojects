switch (hashType) {
#ifndef NO_MD5
        case MD5:
            hLen = MD5_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA
        case SHA:
            hLen = SHA_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA256
        case SHA256:
            hLen = SHA256_DIGEST_SIZE;
            break;
#endif
#ifdef WOLFSSL_SHA512
        case SHA512:
            hLen = SHA512_DIGEST_SIZE;
            break;
#endif
        default:
            return BAD_FUNC_ARG;
    }
