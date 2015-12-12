switch (hmac->macType) {
        #ifndef NO_MD5
        case MD5:
        {
            hmac_block_size = MD5_BLOCK_SIZE;
            if (length <= MD5_BLOCK_SIZE) {
                XMEMCPY(ip, key, length);
            }
            else {
                Md5Update(&hmac->hash.md5, key, length);
                Md5Final(&hmac->hash.md5, ip);
                length = MD5_DIGEST_SIZE;
            }
        }
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
        {
            hmac_block_size = SHA_BLOCK_SIZE;
            if (length <= SHA_BLOCK_SIZE) {
                XMEMCPY(ip, key, length);
            }
            else {
                ShaUpdate(&hmac->hash.sha, key, length);
                ShaFinal(&hmac->hash.sha, ip);
                length = SHA_DIGEST_SIZE;
            }
        }
        break;
        #endif

        #ifndef NO_SHA256
        case SHA256:
        {
    		hmac_block_size = SHA256_BLOCK_SIZE;
            if (length <= SHA256_BLOCK_SIZE) {
                XMEMCPY(ip, key, length);
            }
            else {
                ret = Sha256Update(&hmac->hash.sha256, key, length);
                if (ret != 0)
                    return ret;

                ret = Sha256Final(&hmac->hash.sha256, ip);
                if (ret != 0)
                    return ret;

                length = SHA256_DIGEST_SIZE;
            }
        }
        break;
        #endif

        #ifdef CYASSL_SHA384
        case SHA384:
        {
            hmac_block_size = SHA384_BLOCK_SIZE;
            if (length <= SHA384_BLOCK_SIZE) {
                XMEMCPY(ip, key, length);
            }
            else {
                ret = Sha384Update(&hmac->hash.sha384, key, length);
                if (ret != 0)
                    return ret;

                ret = Sha384Final(&hmac->hash.sha384, ip);
                if (ret != 0)
                    return ret;

                length = SHA384_DIGEST_SIZE;
            }
        }
        break;
        #endif

        #ifdef CYASSL_SHA512
        case SHA512:
        {
            hmac_block_size = SHA512_BLOCK_SIZE;
            if (length <= SHA512_BLOCK_SIZE) {
                XMEMCPY(ip, key, length);
            }
            else {
                ret = Sha512Update(&hmac->hash.sha512, key, length);
                if (ret != 0)
                    return ret;

                ret = Sha512Final(&hmac->hash.sha512, ip);
                if (ret != 0)
                    return ret;

                length = SHA512_DIGEST_SIZE;
            }
        }
        break;
        #endif

        #ifdef HAVE_BLAKE2 
        case BLAKE2B_ID:
        {
            hmac_block_size = BLAKE2B_BLOCKBYTES;
            if (length <= BLAKE2B_BLOCKBYTES) {
                XMEMCPY(ip, key, length);
            }
            else {
                ret = Blake2bUpdate(&hmac->hash.blake2b, key, length);
                if (ret != 0)
                    return ret;

                ret = Blake2bFinal(&hmac->hash.blake2b, ip, BLAKE2B_256);
                if (ret != 0)
                    return ret;

                length = BLAKE2B_256;
            }
        }
        break;
        #endif

        default:
            return BAD_FUNC_ARG;
    }
