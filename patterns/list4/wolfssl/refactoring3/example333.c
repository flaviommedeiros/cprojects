switch (hmac->macType) {
        #ifndef NO_MD5
        case MD5:
            wc_Md5Update(&hmac->hash.md5, (byte*) hmac->ipad, MD5_BLOCK_SIZE);
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
            wc_ShaUpdate(&hmac->hash.sha, (byte*) hmac->ipad, SHA_BLOCK_SIZE);
        break;
        #endif

        #ifndef NO_SHA256
        case SHA256:
            ret = wc_Sha256Update(&hmac->hash.sha256,
                                         (byte*) hmac->ipad, SHA256_BLOCK_SIZE);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef WOLFSSL_SHA384
        case SHA384:
            ret = wc_Sha384Update(&hmac->hash.sha384,
                                         (byte*) hmac->ipad, SHA384_BLOCK_SIZE);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef WOLFSSL_SHA512
        case SHA512:
            ret = wc_Sha512Update(&hmac->hash.sha512,
                                         (byte*) hmac->ipad, SHA512_BLOCK_SIZE);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef HAVE_BLAKE2
        case BLAKE2B_ID:
            ret = wc_Blake2bUpdate(&hmac->hash.blake2b,
                                         (byte*) hmac->ipad,BLAKE2B_BLOCKBYTES);
            if (ret != 0)
                return ret;
        break;
        #endif

        default:
        break;
    }
