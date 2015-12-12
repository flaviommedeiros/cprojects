switch (ctx->cipherType) {

            case AES_128_CBC_TYPE :
            case AES_192_CBC_TYPE :
            case AES_256_CBC_TYPE :
                CYASSL_MSG("AES CBC");
                memcpy(ctx->iv, &ctx->cipher.aes.reg, AES_BLOCK_SIZE);
                break;

#ifdef CYASSL_AES_COUNTER
            case AES_128_CTR_TYPE :
            case AES_192_CTR_TYPE :
            case AES_256_CTR_TYPE :
                CYASSL_MSG("AES CTR");
                memcpy(ctx->iv, &ctx->cipher.aes.reg, AES_BLOCK_SIZE);
                break;
#endif

            case DES_CBC_TYPE :
                CYASSL_MSG("DES CBC");
                memcpy(ctx->iv, &ctx->cipher.des.reg, DES_BLOCK_SIZE);
                break;

            case DES_EDE3_CBC_TYPE :
                CYASSL_MSG("DES EDE3 CBC");
                memcpy(ctx->iv, &ctx->cipher.des.reg, DES_BLOCK_SIZE);
                break;

            case ARC4_TYPE :
                CYASSL_MSG("ARC4");
                break;

            case NULL_CIPHER_TYPE :
                CYASSL_MSG("NULL");
                break;

            default: {
                CYASSL_MSG("bad type");
                return SSL_FATAL_ERROR;
            }
        }
