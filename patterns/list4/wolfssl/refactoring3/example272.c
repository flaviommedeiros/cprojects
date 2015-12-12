switch(hash_type)
    {
#ifndef NO_MD5
        case WC_HASH_TYPE_MD5:
            ret = wc_Md5Hash(data, data_len, hash);
            break;
#endif
#ifndef NO_SHA
        case WC_HASH_TYPE_SHA:
            ret = wc_ShaHash(data, data_len, hash);
            break;
#endif
#ifndef NO_SHA256
        case WC_HASH_TYPE_SHA256:
            ret = wc_Sha256Hash(data, data_len, hash);
            break;
#endif
#ifdef WOLFSSL_SHA512
#ifdef WOLFSSL_SHA384
        case WC_HASH_TYPE_SHA384:
            ret = wc_Sha384Hash(data, data_len, hash);
            break;
#endif /* WOLFSSL_SHA384 */
        case WC_HASH_TYPE_SHA512:
            ret = wc_Sha512Hash(data, data_len, hash);
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
            WOLFSSL_MSG("wc_Hash: Bad hash type");
            ret = BAD_FUNC_ARG;
            break;
    }
