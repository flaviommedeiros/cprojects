if (ssl == NULL
    #ifdef WOLFSSL_SHA384
        || sha384 == NULL
    #endif
        ) {
    #ifdef WOLFSSL_SHA384
        XFREE(sha384, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    #endif
        return MEMORY_E;
    }
