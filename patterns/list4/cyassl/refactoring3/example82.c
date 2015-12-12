switch (ctx->cipherType) {

            case AES_128_CBC_TYPE :
            case AES_192_CBC_TYPE :
            case AES_256_CBC_TYPE :
                CYASSL_MSG("AES CBC");
                if (ctx->enc)
                    ret = AesCbcEncrypt(&ctx->cipher.aes, dst, src, len);
                else
                    ret = AesCbcDecrypt(&ctx->cipher.aes, dst, src, len);
                break;

#ifdef CYASSL_AES_COUNTER
            case AES_128_CTR_TYPE :
            case AES_192_CTR_TYPE :
            case AES_256_CTR_TYPE :
                    CYASSL_MSG("AES CTR");
                    AesCtrEncrypt(&ctx->cipher.aes, dst, src, len);
                break;
#endif

            case DES_CBC_TYPE :
                if (ctx->enc)
                    Des_CbcEncrypt(&ctx->cipher.des, dst, src, len);
                else
                    Des_CbcDecrypt(&ctx->cipher.des, dst, src, len);
                break;

            case DES_EDE3_CBC_TYPE :
                if (ctx->enc)
                    ret = Des3_CbcEncrypt(&ctx->cipher.des3, dst, src, len);
                else
                    ret = Des3_CbcDecrypt(&ctx->cipher.des3, dst, src, len);
                break;

            case ARC4_TYPE :
                Arc4Process(&ctx->cipher.arc4, dst, src, len);
                break;

            case NULL_CIPHER_TYPE :
                XMEMCPY(dst, src, len);
                break;

            default: {
                CYASSL_MSG("bad type");
                return 0;  /* failure */
            }
        }
