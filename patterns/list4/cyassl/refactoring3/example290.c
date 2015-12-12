switch (type) {
        #ifndef NO_MD5
        case MD5:
            return MD5_DIGEST_SIZE;
        break;
        #endif

        #ifndef NO_SHA
        case SHA:
            return SHA_DIGEST_SIZE;
        break;
        #endif
        
        #ifndef NO_SHA256
        case SHA256:
            return SHA256_DIGEST_SIZE;
        break;
        #endif
        
        #ifdef CYASSL_SHA384
        case SHA384:
            return SHA384_DIGEST_SIZE;
        break;
        #endif
        
        #ifdef CYASSL_SHA512
        case SHA512:
            return SHA512_DIGEST_SIZE;
        break;
        #endif
        
        #ifdef HAVE_BLAKE2 
        case BLAKE2B_ID:
            return BLAKE2B_OUTBYTES;
        break;
        #endif
        
        default:
            return BAD_FUNC_ARG;
        break;
    }
