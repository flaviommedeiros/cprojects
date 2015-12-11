switch (sig_alg) {
# ifndef OPENSSL_NO_RSA
        case TLSEXT_signature_rsa:
            idx = SSL_PKEY_RSA_SIGN;
            break;
# endif
# ifndef OPENSSL_NO_DSA
        case TLSEXT_signature_dsa:
            idx = SSL_PKEY_DSA_SIGN;
            break;
# endif
# ifndef OPENSSL_NO_ECDSA
        case TLSEXT_signature_ecdsa:
            idx = SSL_PKEY_ECC;
            break;
# endif
        default:
            continue;
        }
