switch (ctx->macType) {
#ifndef NO_MD5
            case MD5:
                wolfSSL_MD5_Update((MD5_CTX*)&ctx->hash, data,
                                  (unsigned long)sz);
                break;
#endif
#ifndef NO_SHA
            case SHA:
                wolfSSL_SHA_Update((SHA_CTX*)&ctx->hash, data,
                                  (unsigned long)sz);
                break;
#endif
#ifndef NO_SHA256
            case SHA256:
                wolfSSL_SHA256_Update((SHA256_CTX*)&ctx->hash, data,
                                     (unsigned long)sz);
                break;
#endif
#ifdef WOLFSSL_SHA384
            case SHA384:
                wolfSSL_SHA384_Update((SHA384_CTX*)&ctx->hash, data,
                                     (unsigned long)sz);
                break;
#endif
#ifdef WOLFSSL_SHA512
            case SHA512:
                wolfSSL_SHA512_Update((SHA512_CTX*)&ctx->hash, data,
                                     (unsigned long)sz);
                break;
#endif
            default:
                return BAD_FUNC_ARG;
        }
