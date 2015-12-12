switch (second) {

#ifndef NO_RSA
        case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;

#ifndef NO_DES3
        case TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;
#endif

#ifndef NO_RC4
        case TLS_ECDHE_RSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;
#endif
#endif /* NO_RSA */

#ifndef NO_DES3
        case TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;
#endif
#ifndef NO_RC4
        case TLS_ECDHE_ECDSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_RC4_128_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;
#endif
#ifndef NO_RSA
        case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;
#endif

        case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;

        case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;

        case TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256 :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;

#ifndef NO_RSA
        case TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_RSA)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256 :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384 :
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;

        case TLS_RSA_WITH_AES_128_CCM_8 :
        case TLS_RSA_WITH_AES_256_CCM_8 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;

        case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 :
        case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 :
            if (requirement == REQUIRES_RSA)
                return 1;
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            break;

        case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 :
        case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384 :
            if (requirement == REQUIRES_RSA_SIG)
                return 1;
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;
#endif

        case TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8 :
        case TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8 :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 :
        case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            break;

        case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 :
        case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 :
            if (requirement == REQUIRES_ECC_DSA)
                return 1;
            if (requirement == REQUIRES_ECC_STATIC)
                return 1;
            break;

        case TLS_PSK_WITH_AES_128_CCM:
        case TLS_PSK_WITH_AES_256_CCM:
        case TLS_PSK_WITH_AES_128_CCM_8:
        case TLS_PSK_WITH_AES_256_CCM_8:
            if (requirement == REQUIRES_PSK)
                return 1;
            break;

        case TLS_DHE_PSK_WITH_AES_128_CCM:
        case TLS_DHE_PSK_WITH_AES_256_CCM:
            if (requirement == REQUIRES_PSK)
                return 1;
            if (requirement == REQUIRES_DHE)
                return 1;
            break;

        default:
            CYASSL_MSG("Unsupported cipher suite, CipherRequires ECC");
            return 0;
        }
