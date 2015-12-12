switch (type) {
        #ifndef NO_MD5
        case MD5:
            wc_InitMd5(&hmac->hash.md5);
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
            ret = wc_InitSha(&hmac->hash.sha);
        break;
        #endif

        #ifndef NO_SHA256
        case SHA256:
            ret = wc_InitSha256(&hmac->hash.sha256);
        break;
        #endif

        #ifdef WOLFSSL_SHA384
        case SHA384:
            ret = wc_InitSha384(&hmac->hash.sha384);
        break;
        #endif

        #ifdef WOLFSSL_SHA512
        case SHA512:
            ret = wc_InitSha512(&hmac->hash.sha512);
        break;
        #endif

        #ifdef HAVE_BLAKE2
        case BLAKE2B_ID:
            ret = wc_InitBlake2b(&hmac->hash.blake2b, BLAKE2B_256);
        break;
        #endif

        default:
            return BAD_FUNC_ARG;
    }
