switch (ctx->cipherType) {

#ifndef NO_AES
            case AES_128_CBC_TYPE :
            case AES_192_CBC_TYPE :
            case AES_256_CBC_TYPE :
                WOLFSSL_MSG("AES CBC");
                XMEMCPY(ctx->iv, &ctx->cipher.aes.reg, AES_BLOCK_SIZE);
                break;

#ifdef WOLFSSL_AES_COUNTER
            case AES_128_CTR_TYPE :
            case AES_192_CTR_TYPE :
            case AES_256_CTR_TYPE :
                WOLFSSL_MSG("AES CTR");
                XMEMCPY(ctx->iv, &ctx->cipher.aes.reg, AES_BLOCK_SIZE);
                break;
#endif /* WOLFSSL_AES_COUNTER */

#endif /* NO_AES */

#ifndef NO_DES3
            case DES_CBC_TYPE :
                WOLFSSL_MSG("DES CBC");
                XMEMCPY(ctx->iv, &ctx->cipher.des.reg, DES_BLOCK_SIZE);
                break;

            case DES_EDE3_CBC_TYPE :
                WOLFSSL_MSG("DES EDE3 CBC");
                XMEMCPY(ctx->iv, &ctx->cipher.des3.reg, DES_BLOCK_SIZE);
                break;
#endif

#ifdef HAVE_IDEA
            case IDEA_CBC_TYPE :
                WOLFSSL_MSG("IDEA CBC");
                XMEMCPY(ctx->iv, &ctx->cipher.idea.reg, IDEA_BLOCK_SIZE);
                break;
#endif
            case ARC4_TYPE :
                WOLFSSL_MSG("ARC4");
                break;

            case NULL_CIPHER_TYPE :
                WOLFSSL_MSG("NULL");
                break;

            default: {
                WOLFSSL_MSG("bad type");
                return SSL_FATAL_ERROR;
            }
        }
