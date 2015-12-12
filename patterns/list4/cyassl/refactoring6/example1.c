if (ssl == NULL
    #ifndef NO_OLD_TLS
    #ifndef NO_MD5
        || md5 == NULL
    #endif
    #ifndef NO_SHA
        || sha == NULL
    #endif
    #endif
    #ifndef NO_SHA256
        || sha256 == NULL
    #endif
    #ifdef CYASSL_SHA384
        || sha384 == NULL
    #endif
        ) {
    #ifndef NO_OLD_TLS
    #ifndef NO_MD5
        XFREE(md5, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    #endif
    #ifndef NO_SHA
        XFREE(sha, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    #endif
    #endif
    #ifndef NO_SHA256
        XFREE(sha256, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    #endif
    #ifdef CYASSL_SHA384
        XFREE(sha384, NULL, DYNAMIC_TYPE_TMP_BUFFER);
    #endif
        return MEMORY_E;
    }
