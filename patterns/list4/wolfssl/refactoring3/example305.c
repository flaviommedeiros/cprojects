switch (type) {
#ifdef WOLFSSL_MD2
        case MD2:
            return MD2h;
#endif
#ifndef NO_MD5
        case MD5:
            return MD5h;
#endif
#ifndef NO_SHA
        case SHA:
            return SHAh;
#endif
#ifndef NO_SHA256
        case SHA256:
            return SHA256h;
#endif
#ifdef WOLFSSL_SHA384
        case SHA384:
            return SHA384h;
#endif
#ifdef WOLFSSL_SHA512
        case SHA512:
            return SHA512h;
#endif
        default:
            return 0;
    }
