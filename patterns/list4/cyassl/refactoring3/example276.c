switch (hmac->macType) {
        #ifndef NO_MD5
        case MD5:
            Md5Update(&hmac->hash.md5, msg, length);
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
            ShaUpdate(&hmac->hash.sha, msg, length);
        break;
        #endif

        #ifndef NO_SHA256
        case SHA256:
            ret = Sha256Update(&hmac->hash.sha256, msg, length);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef CYASSL_SHA384
        case SHA384:
            ret = Sha384Update(&hmac->hash.sha384, msg, length);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef CYASSL_SHA512
        case SHA512:
            ret = Sha512Update(&hmac->hash.sha512, msg, length);
            if (ret != 0)
                return ret;
        break;
        #endif

        #ifdef HAVE_BLAKE2 
        case BLAKE2B_ID:
            ret = Blake2bUpdate(&hmac->hash.blake2b, msg, length);
            if (ret != 0)
                return ret;
        break;
        #endif

        default:
        break;
    }
