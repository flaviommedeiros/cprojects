switch(sig_type) {
#ifdef HAVE_ECC
        case WC_SIGNATURE_TYPE_ECC:
        {
            if (key_len >= sizeof(ecc_key)) {
                sig_len = wc_ecc_sig_size((ecc_key*)key);
            }
            else {
                WOLFSSL_MSG("wc_SignatureGetSize: Invalid ECC key size");
            }
            break;
        }
#endif
#ifndef NO_RSA
        case WC_SIGNATURE_TYPE_RSA:
            if (key_len >= sizeof(RsaKey)) {
                sig_len = wc_RsaEncryptSize((RsaKey*)key);
            }
            else {
                WOLFSSL_MSG("wc_SignatureGetSize: Invalid RsaKey key size");
            }
            break;
#endif

        case WC_SIGNATURE_TYPE_NONE:
        default:
            break;
    }
