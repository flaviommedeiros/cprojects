switch (ctx->cipherType) {

        case AES_128_CBC_TYPE :
        case AES_192_CBC_TYPE :
        case AES_256_CBC_TYPE :
            CYASSL_MSG("AES CBC");
            return AES_BLOCK_SIZE;

#ifdef CYASSL_AES_COUNTER
        case AES_128_CTR_TYPE :
        case AES_192_CTR_TYPE :
        case AES_256_CTR_TYPE :
            CYASSL_MSG("AES CTR");
            return AES_BLOCK_SIZE;
#endif

        case DES_CBC_TYPE :
            CYASSL_MSG("DES CBC");
            return DES_BLOCK_SIZE;

        case DES_EDE3_CBC_TYPE :
            CYASSL_MSG("DES EDE3 CBC");
            return DES_BLOCK_SIZE;

        case ARC4_TYPE :
            CYASSL_MSG("ARC4");
            return 0;

        case NULL_CIPHER_TYPE :
            CYASSL_MSG("NULL");
            return 0;

        default: {
            CYASSL_MSG("bad type");
        }
    }
