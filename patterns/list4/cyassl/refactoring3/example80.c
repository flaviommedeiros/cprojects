switch (version) {
#ifndef NO_OLD_TLS
        case CYASSL_SSLV3:
            ssl->options.minDowngrade = SSLv3_MINOR;
            break;
#endif

#ifndef NO_TLS
    #ifndef NO_OLD_TLS
        case CYASSL_TLSV1:
            ssl->options.minDowngrade = TLSv1_MINOR;
            break;

        case CYASSL_TLSV1_1:
            ssl->options.minDowngrade = TLSv1_1_MINOR;
            break;
    #endif
        case CYASSL_TLSV1_2:
            ssl->options.minDowngrade = TLSv1_2_MINOR;
            break;
#endif

        default:
            CYASSL_MSG("Bad function argument");
            return BAD_FUNC_ARG;
    }
