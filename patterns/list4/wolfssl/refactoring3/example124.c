switch (cipher->ssl->options.cipherSuite) {
#ifndef NO_RSA
#ifndef NO_RC4
    #ifndef NO_SHA
            case SSL_RSA_WITH_RC4_128_SHA :
                return "SSL_RSA_WITH_RC4_128_SHA";
    #endif
    #ifndef NO_MD5
            case SSL_RSA_WITH_RC4_128_MD5 :
                return "SSL_RSA_WITH_RC4_128_MD5";
    #endif
#endif
#ifndef NO_SHA
    #ifndef NO_DES3
            case SSL_RSA_WITH_3DES_EDE_CBC_SHA :
                return "SSL_RSA_WITH_3DES_EDE_CBC_SHA";
    #endif
    #ifdef HAVE_IDEA
            case SSL_RSA_WITH_IDEA_CBC_SHA :
                return "SSL_RSA_WITH_IDEA_CBC_SHA";
    #endif

            case TLS_RSA_WITH_AES_128_CBC_SHA :
                return "TLS_RSA_WITH_AES_128_CBC_SHA";
            case TLS_RSA_WITH_AES_256_CBC_SHA :
                return "TLS_RSA_WITH_AES_256_CBC_SHA";
#endif
            case TLS_RSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_RSA_WITH_AES_128_CBC_SHA256";
            case TLS_RSA_WITH_AES_256_CBC_SHA256 :
                return "TLS_RSA_WITH_AES_256_CBC_SHA256";
    #ifdef HAVE_BLAKE2
            case TLS_RSA_WITH_AES_128_CBC_B2B256:
                return "TLS_RSA_WITH_AES_128_CBC_B2B256";
            case TLS_RSA_WITH_AES_256_CBC_B2B256:
                return "TLS_RSA_WITH_AES_256_CBC_B2B256";
    #endif
#ifndef NO_SHA
            case TLS_RSA_WITH_NULL_SHA :
                return "TLS_RSA_WITH_NULL_SHA";
#endif
            case TLS_RSA_WITH_NULL_SHA256 :
                return "TLS_RSA_WITH_NULL_SHA256";
#endif /* NO_RSA */
#ifndef NO_PSK
#ifndef NO_SHA
            case TLS_PSK_WITH_AES_128_CBC_SHA :
                return "TLS_PSK_WITH_AES_128_CBC_SHA";
            case TLS_PSK_WITH_AES_256_CBC_SHA :
                return "TLS_PSK_WITH_AES_256_CBC_SHA";
#endif
#ifndef NO_SHA256
            case TLS_PSK_WITH_AES_128_CBC_SHA256 :
                return "TLS_PSK_WITH_AES_128_CBC_SHA256";
            case TLS_PSK_WITH_NULL_SHA256 :
                return "TLS_PSK_WITH_NULL_SHA256";
            case TLS_DHE_PSK_WITH_AES_128_CBC_SHA256 :
                return "TLS_DHE_PSK_WITH_AES_128_CBC_SHA256";
            case TLS_DHE_PSK_WITH_NULL_SHA256 :
                return "TLS_DHE_PSK_WITH_NULL_SHA256";
    #ifdef HAVE_AESGCM
            case TLS_PSK_WITH_AES_128_GCM_SHA256 :
                return "TLS_PSK_WITH_AES_128_GCM_SHA256";
            case TLS_DHE_PSK_WITH_AES_128_GCM_SHA256 :
                return "TLS_DHE_PSK_WITH_AES_128_GCM_SHA256";
    #endif
#endif
#ifdef WOLFSSL_SHA384
            case TLS_PSK_WITH_AES_256_CBC_SHA384 :
                return "TLS_PSK_WITH_AES_256_CBC_SHA384";
            case TLS_PSK_WITH_NULL_SHA384 :
                return "TLS_PSK_WITH_NULL_SHA384";
            case TLS_DHE_PSK_WITH_AES_256_CBC_SHA384 :
                return "TLS_DHE_PSK_WITH_AES_256_CBC_SHA384";
            case TLS_DHE_PSK_WITH_NULL_SHA384 :
                return "TLS_DHE_PSK_WITH_NULL_SHA384";
    #ifdef HAVE_AESGCM
            case TLS_PSK_WITH_AES_256_GCM_SHA384 :
                return "TLS_PSK_WITH_AES_256_GCM_SHA384";
            case TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 :
                return "TLS_DHE_PSK_WITH_AES_256_GCM_SHA384";
    #endif
#endif
#ifndef NO_SHA
            case TLS_PSK_WITH_NULL_SHA :
                return "TLS_PSK_WITH_NULL_SHA";
#endif
#endif /* NO_PSK */
#ifndef NO_RSA
            case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 :
                return "TLS_DHE_RSA_WITH_AES_128_CBC_SHA256";
            case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 :
                return "TLS_DHE_RSA_WITH_AES_256_CBC_SHA256";
#ifndef NO_SHA
            case TLS_DHE_RSA_WITH_AES_128_CBC_SHA :
                return "TLS_DHE_RSA_WITH_AES_128_CBC_SHA";
            case TLS_DHE_RSA_WITH_AES_256_CBC_SHA :
                return "TLS_DHE_RSA_WITH_AES_256_CBC_SHA";
#endif
#ifndef NO_HC128
    #ifndef NO_MD5
            case TLS_RSA_WITH_HC_128_MD5 :
                return "TLS_RSA_WITH_HC_128_MD5";
    #endif
    #ifndef NO_SHA
            case TLS_RSA_WITH_HC_128_SHA :
                return "TLS_RSA_WITH_HC_128_SHA";
    #endif
    #ifdef HAVE_BLAKE2
            case TLS_RSA_WITH_HC_128_B2B256:
                return "TLS_RSA_WITH_HC_128_B2B256";
    #endif
#endif /* NO_HC128 */
#ifndef NO_SHA
    #ifndef NO_RABBIT
            case TLS_RSA_WITH_RABBIT_SHA :
                return "TLS_RSA_WITH_RABBIT_SHA";
    #endif
    #ifdef HAVE_NTRU
        #ifndef NO_RC4
            case TLS_NTRU_RSA_WITH_RC4_128_SHA :
                return "TLS_NTRU_RSA_WITH_RC4_128_SHA";
        #endif
        #ifndef NO_DES3
            case TLS_NTRU_RSA_WITH_3DES_EDE_CBC_SHA :
                return "TLS_NTRU_RSA_WITH_3DES_EDE_CBC_SHA";
        #endif
            case TLS_NTRU_RSA_WITH_AES_128_CBC_SHA :
                return "TLS_NTRU_RSA_WITH_AES_128_CBC_SHA";
            case TLS_NTRU_RSA_WITH_AES_256_CBC_SHA :
                return "TLS_NTRU_RSA_WITH_AES_256_CBC_SHA";
    #endif /* HAVE_NTRU */
    #ifdef HAVE_QSH
            case TLS_QSH :
                return "TLS_QSH";
    #endif /* HAVE_QSH*/
#endif /* NO_SHA */
            case TLS_RSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_RSA_WITH_AES_128_GCM_SHA256";
            case TLS_RSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_RSA_WITH_AES_256_GCM_SHA384";
            case TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 :
                return "TLS_DHE_RSA_WITH_AES_128_GCM_SHA256";
            case TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 :
                return "TLS_DHE_RSA_WITH_AES_256_GCM_SHA384";
#ifndef NO_SHA
            case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA :
                return "TLS_RSA_WITH_CAMELLIA_128_CBC_SHA";
            case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA :
                return "TLS_RSA_WITH_CAMELLIA_256_CBC_SHA";
#endif
            case TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
                return "TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256";
            case TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
                return "TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256";
#ifndef NO_SHA
            case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA :
                return "TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA";
            case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA :
                return "TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA";
#endif
            case TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256 :
                return "TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256";
            case TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256 :
                return "TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256";
#endif /* NO_RSA */
#ifdef BUILD_TLS_DH_anon_WITH_AES_128_CBC_SHA
            case TLS_DH_anon_WITH_AES_128_CBC_SHA :
                return "TLS_DH_anon_WITH_AES_128_CBC_SHA";
#endif
            default:
                return "NONE";
        }
