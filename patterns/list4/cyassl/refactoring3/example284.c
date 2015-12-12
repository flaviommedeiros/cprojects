switch (hmac->macType) {
        #ifndef NO_MD5
        case MD5:
        {
            Md5Final(&hmac->hash.md5, (byte*) hmac->innerHash);

            Md5Update(&hmac->hash.md5, (byte*) hmac->opad, MD5_BLOCK_SIZE);
            Md5Update(&hmac->hash.md5,
                                     (byte*) hmac->innerHash, MD5_DIGEST_SIZE);

            Md5Final(&hmac->hash.md5, hash);
        }
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
        {
            ShaFinal(&hmac->hash.sha, (byte*) hmac->innerHash);

            ShaUpdate(&hmac->hash.sha, (byte*) hmac->opad, SHA_BLOCK_SIZE);
            ShaUpdate(&hmac->hash.sha,
                                     (byte*) hmac->innerHash, SHA_DIGEST_SIZE);

            ShaFinal(&hmac->hash.sha, hash);
        }
        break;
        #endif

        #ifndef NO_SHA256
        case SHA256:
        {
            ret = Sha256Final(&hmac->hash.sha256, (byte*) hmac->innerHash);
            if (ret != 0)
                return ret;

            ret = Sha256Update(&hmac->hash.sha256,
                                (byte*) hmac->opad, SHA256_BLOCK_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha256Update(&hmac->hash.sha256,
                                (byte*) hmac->innerHash, SHA256_DIGEST_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha256Final(&hmac->hash.sha256, hash);
            if (ret != 0)
                return ret;
        }
        break;
        #endif

        #ifdef CYASSL_SHA384
        case SHA384:
        {
            ret = Sha384Final(&hmac->hash.sha384, (byte*) hmac->innerHash);
            if (ret != 0)
                return ret;

            ret = Sha384Update(&hmac->hash.sha384,
                                 (byte*) hmac->opad, SHA384_BLOCK_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha384Update(&hmac->hash.sha384,
                                 (byte*) hmac->innerHash, SHA384_DIGEST_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha384Final(&hmac->hash.sha384, hash);
            if (ret != 0)
                return ret;
        }
        break;
        #endif

        #ifdef CYASSL_SHA512
        case SHA512:
        {
            ret = Sha512Final(&hmac->hash.sha512, (byte*) hmac->innerHash);
            if (ret != 0)
                return ret;

            ret = Sha512Update(&hmac->hash.sha512,
                                 (byte*) hmac->opad, SHA512_BLOCK_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha512Update(&hmac->hash.sha512,
                                 (byte*) hmac->innerHash, SHA512_DIGEST_SIZE);
            if (ret != 0)
                return ret;

            ret = Sha512Final(&hmac->hash.sha512, hash);
            if (ret != 0)
                return ret;
        }
        break;
        #endif

        #ifdef HAVE_BLAKE2 
        case BLAKE2B_ID:
        {
            ret = Blake2bFinal(&hmac->hash.blake2b, (byte*) hmac->innerHash,
                         BLAKE2B_256);
            if (ret != 0)
                return ret;

            ret = Blake2bUpdate(&hmac->hash.blake2b,
                                 (byte*) hmac->opad, BLAKE2B_BLOCKBYTES);
            if (ret != 0)
                return ret;

            ret = Blake2bUpdate(&hmac->hash.blake2b,
                                 (byte*) hmac->innerHash, BLAKE2B_256);
            if (ret != 0)
                return ret;

            ret = Blake2bFinal(&hmac->hash.blake2b, hash, BLAKE2B_256);
            if (ret != 0)
                return ret;
        }
        break;
        #endif

        default:
        break;
    }
