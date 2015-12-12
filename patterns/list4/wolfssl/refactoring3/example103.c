switch (cipher->ssl->options.cipherSuite) {
#ifdef HAVE_ECC
#ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256";
#endif
            case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256";
#ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256";
#endif
            case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256";
#ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 :
                return "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384";
#endif
            case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 :
                return "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384";
#ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384 :
                return "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384";
#endif
            case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 :
                return "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384";
#ifndef NO_SHA
#ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA :
                return "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA";
            case TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA :
                return "TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA";
#endif
            case TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA :
                return "TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA";
            case TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA :
                return "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA";
#ifndef NO_RC4
    #ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_RC4_128_SHA :
                return "TLS_ECDHE_RSA_WITH_RC4_128_SHA";
    #endif
            case TLS_ECDHE_ECDSA_WITH_RC4_128_SHA :
                return "TLS_ECDHE_ECDSA_WITH_RC4_128_SHA";
#endif
#ifndef NO_DES3
    #ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA :
                return "TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA";
    #endif
            case TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA :
                return "TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA";
#endif

#ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_AES_128_CBC_SHA :
                return "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA";
            case TLS_ECDH_RSA_WITH_AES_256_CBC_SHA :
                return "TLS_ECDH_RSA_WITH_AES_256_CBC_SHA";
#endif
            case TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA :
                return "TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA";
            case TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA :
                return "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA";
#ifndef NO_RC4
    #ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_RC4_128_SHA :
                return "TLS_ECDH_RSA_WITH_RC4_128_SHA";
    #endif
            case TLS_ECDH_ECDSA_WITH_RC4_128_SHA :
                return "TLS_ECDH_ECDSA_WITH_RC4_128_SHA";
#endif
#ifndef NO_DES3
    #ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA :
                return "TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA";
    #endif
            case TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA :
                return "TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA";
#endif
#endif /* NO_SHA */

#ifdef HAVE_AESGCM
#ifndef NO_RSA
            case TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256";
            case TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384";
#endif
            case TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256";
            case TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384";
#ifndef NO_RSA
            case TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256";
            case TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384";
#endif
            case TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256";
            case TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384";
#endif
#endif /* HAVE_ECC */

#ifdef HAVE_AESCCM
#ifndef NO_RSA
            case TLS_RSA_WITH_AES_128_CCM_8 :
                return "TLS_RSA_WITH_AES_128_CCM_8";
            case TLS_RSA_WITH_AES_256_CCM_8 :
                return "TLS_RSA_WITH_AES_256_CCM_8";
#endif
#ifndef NO_PSK
            case TLS_PSK_WITH_AES_128_CCM_8 :
                return "TLS_PSK_WITH_AES_128_CCM_8";
            case TLS_PSK_WITH_AES_256_CCM_8 :
                return "TLS_PSK_WITH_AES_256_CCM_8";
            case TLS_PSK_WITH_AES_128_CCM :
                return "TLS_PSK_WITH_AES_128_CCM";
            case TLS_PSK_WITH_AES_256_CCM :
                return "TLS_PSK_WITH_AES_256_CCM";
            case TLS_DHE_PSK_WITH_AES_128_CCM :
                return "TLS_DHE_PSK_WITH_AES_128_CCM";
            case TLS_DHE_PSK_WITH_AES_256_CCM :
                return "TLS_DHE_PSK_WITH_AES_256_CCM";
#endif
#ifdef HAVE_ECC
            case TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8:
                return "TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8";
            case TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8 :
                return "TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8";
#endif
#endif

            default:
                return "NONE";
        }
