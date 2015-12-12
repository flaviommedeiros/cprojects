switch (type) {
        #ifndef NO_MD5
        case MD5:
            return MD5_DIGEST_SIZE;
        #endif

        #ifndef NO_SHA
        case SHA:
            return SHA_DIGEST_SIZE;
        #endif

        #ifndef NO_SHA256
        case SHA256:
            return SHA256_DIGEST_SIZE;
        #endif

        #ifdef WOLFSSL_SHA384
        case SHA384:
            return SHA384_DIGEST_SIZE;
        #endif

        #ifdef WOLFSSL_SHA512
        case SHA512:
            return SHA512_DIGEST_SIZE;
        #endif

        #ifdef HAVE_BLAKE2
        case BLAKE2B_ID:
            return BLAKE2B_OUTBYTES;
        #endif

        default:
            return BAD_FUNC_ARG;
    }
