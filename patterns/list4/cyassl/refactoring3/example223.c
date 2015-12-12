switch (version) {
#ifndef NO_OLD_TLS
        case 0:
            method = CyaSSLv3_client_method();
            break;
                
                
    #ifndef NO_TLS
        case 1:
            method = CyaTLSv1_client_method();
            break;

        case 2:
            method = CyaTLSv1_1_client_method();
            break;
    #endif /* NO_TLS */
                
#endif  /* NO_OLD_TLS */
                
#ifndef NO_TLS
        case 3:
            method = CyaTLSv1_2_client_method();
            break;
#endif

#ifdef CYASSL_DTLS
        case -1:
            method = CyaDTLSv1_client_method();
            break;

        case -2:
            method = CyaDTLSv1_2_client_method();
            break;
#endif

        default:
            err_sys("Bad SSL version");
            break;
    }
