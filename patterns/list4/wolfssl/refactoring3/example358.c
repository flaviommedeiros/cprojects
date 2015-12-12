switch (version) {
#ifndef NO_OLD_TLS
    #ifdef WOLFSSL_ALLOW_SSLV3
        case 0:
            method = wolfSSLv3_client_method();
            break;
    #endif

    #ifndef NO_TLS
        case 1:
            method = wolfTLSv1_client_method();
            break;

        case 2:
            method = wolfTLSv1_1_client_method();
            break;
    #endif /* NO_TLS */

#endif  /* NO_OLD_TLS */

#ifndef NO_TLS
        case 3:
            method = wolfTLSv1_2_client_method();
            break;
#endif

#ifdef WOLFSSL_DTLS
        #ifndef NO_OLD_TLS
        case -1:
            method = wolfDTLSv1_client_method();
            break;
        #endif

        case -2:
            method = wolfDTLSv1_2_client_method();
            break;
#endif

        default:
            err_sys("Bad SSL version");
            break;
    }
