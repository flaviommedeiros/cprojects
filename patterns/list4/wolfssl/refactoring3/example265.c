switch(hash_type)
    {
#ifndef NO_MD5
        case WC_HASH_TYPE_MD5:
            dig_size = MD5_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA
        case WC_HASH_TYPE_SHA:
            dig_size = SHA_DIGEST_SIZE;
            break;
#endif
#ifndef NO_SHA256
        case WC_HASH_TYPE_SHA256:
            dig_size = SHA256_DIGEST_SIZE;
            break;
#endif
#ifdef WOLFSSL_SHA512
#ifdef WOLFSSL_SHA384
        case WC_HASH_TYPE_SHA384:
            dig_size = SHA384_DIGEST_SIZE;
            break;
#endif /* WOLFSSL_SHA384 */
        case WC_HASH_TYPE_SHA512:
            dig_size = SHA512_DIGEST_SIZE;
            break;
#endif /* WOLFSSL_SHA512 */

        /* Not Supported */
#ifdef WOLFSSL_MD2
        case WC_HASH_TYPE_MD2:
#endif
#ifndef NO_MD4
        case WC_HASH_TYPE_MD4:
#endif
        case WC_HASH_TYPE_NONE:
        default:
            dig_size = BAD_FUNC_ARG;
            break;
    }
