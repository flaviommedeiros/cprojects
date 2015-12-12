switch (second) {

#ifndef NO_RSA
        case SSL_RSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_NTRU_RSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_NTRU)
                return 1;
            break;

        case SSL_RSA_WITH_RC4_128_MD5 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case SSL_RSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_NTRU_RSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_NTRU)
                return 1;
            break;

        case TLS_RSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_AES_128_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_NTRU_RSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_NTRU)
                return 1;
            break;

        case TLS_RSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_AES_256_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_NULL_SHA :
        case TLS_RSA_WITH_NULL_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_NTRU_RSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_NTRU)
                return 1;
            break;
#endif

        case TLS_PSK_WITH_AES_128_GCM_SHA256 :
        case TLS_PSK_WITH_AES_256_GCM_SHA384 :
        case TLS_PSK_WITH_AES_128_CBC_SHA256 :
        case TLS_PSK_WITH_AES_256_CBC_SHA384 :
        case TLS_PSK_WITH_AES_128_CBC_SHA :
        case TLS_PSK_WITH_AES_256_CBC_SHA :
        case TLS_PSK_WITH_NULL_SHA384 :
        case TLS_PSK_WITH_NULL_SHA256 :
        case TLS_PSK_WITH_NULL_SHA :
            if (requirement == REQUIRES_PSK)
                return 1;
            break;

        case TLS_DHE_PSK_WITH_AES_128_GCM_SHA256 :
        case TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 :
        case TLS_DHE_PSK_WITH_AES_128_CBC_SHA256 :
        case TLS_DHE_PSK_WITH_AES_256_CBC_SHA384 :
        case TLS_DHE_PSK_WITH_NULL_SHA384 :
        case TLS_DHE_PSK_WITH_NULL_SHA256 :
            if (requirement == REQUIRES_DHE)
                return 1;
            if (requirement == REQUIRES_PSK)
                return 1;
            break;

#ifndef NO_RSA
        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        case TLS_RSA_WITH_HC_128_MD5 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_HC_128_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_HC_128_B2B256:
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_AES_128_CBC_B2B256:
        case TLS_RSA_WITH_AES_256_CBC_B2B256:
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_RABBIT_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_RSA_WITH_AES_128_GCM_SHA256 :
        case TLS_RSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 :
        case TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA :
        case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA :
        case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
        case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA :
        case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA :
        case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
        case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;
#endif
#ifdef HAVE_ANON
        case TLS_DH_anon_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_DHE)
                return 1;
            break;
#endif

        default:
            CYASSL_MSG("Unsupported cipher suite, CipherRequires");
            return 0;
        }
