switch (hash) {
        #ifndef NO_MD5
            case md5_mac:
                hash = MD5;
                len  = MD5_DIGEST_SIZE;
            break;
        #endif

        #ifndef NO_SHA256
            case sha256_mac:
                hash = SHA256;
                len  = SHA256_DIGEST_SIZE;
            break;
        #endif

        #ifdef WOLFSSL_SHA384
            case sha384_mac:
                hash = SHA384;
                len  = SHA384_DIGEST_SIZE;
            break;
        #endif

        #ifndef NO_SHA
            case sha_mac:
            default:
                hash = SHA;
                len  = SHA_DIGEST_SIZE;
            break;
        #endif
    }
