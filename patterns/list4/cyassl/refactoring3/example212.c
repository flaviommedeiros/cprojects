switch (ssl->specs.mac_algorithm) {
        #ifndef NO_MD5
        case md5_mac:
        {
            return MD5;
        }
        #endif
        #ifndef NO_SHA256
        case sha256_mac:
        {
            return SHA256;
        }
        #endif
        #ifdef CYASSL_SHA384
        case sha384_mac:
        {
            return SHA384;
        }

        #endif
        #ifndef NO_SHA
        case sha_mac:
        {
            return SHA;
        }
        #endif
        #ifdef HAVE_BLAKE2 
        case blake2b_mac:
        {
            return BLAKE2B_ID; 
        }
        #endif
        default:
        {
            return SSL_FATAL_ERROR;
        }
    }
