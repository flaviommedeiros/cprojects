switch (version) {
#ifndef NO_OLD_TLS
        case CYASSL_SSLV3:
            ssl->version = MakeSSLv3();
            break;
#endif

#ifndef NO_TLS
    #ifndef NO_OLD_TLS
        case CYASSL_TLSV1:
            ssl->version = MakeTLSv1();
            break;

        case CYASSL_TLSV1_1:
            ssl->version = MakeTLSv1_1();
            break;
    #endif
        case CYASSL_TLSV1_2:
            ssl->version = MakeTLSv1_2();
            break;
#endif

        default:
            CYASSL_MSG("Bad function argument");
            return BAD_FUNC_ARG;
    }
