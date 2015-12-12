switch (hashType) {
#ifndef NO_MD5
        case MD5:
            *v = MD5_BLOCK_SIZE;
            *u = MD5_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA
        case SHA:
            *v = SHA_BLOCK_SIZE;
            *u = SHA_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA256
        case SHA256:
            *v = SHA256_BLOCK_SIZE;
            *u = SHA256_DIGEST_SIZE;
            break;
#endif
#ifdef WOLFSSL_SHA512
        case SHA512:
            *v = SHA512_BLOCK_SIZE;
            *u = SHA512_DIGEST_SIZE;
            break;
#endif
        default:
            return BAD_FUNC_ARG;
    }
