switch(sig_type) {
#ifdef HAVE_ECC
            case WC_SIGNATURE_TYPE_ECC:
            {
                /* Create signature using provided ECC key */
                ret = wc_ecc_sign_hash(hash_data, hash_len, sig, sig_len, rng, (ecc_key*)key);
                break;
            }
#endif
#ifndef NO_RSA
            case WC_SIGNATURE_TYPE_RSA:
                /* Create signature using provided RSA key */
                ret = wc_RsaSSL_Sign(hash_data, hash_len, sig, *sig_len, (RsaKey*)key, rng);
                if (ret > 0) {
                    *sig_len = ret;
                }
                break;
#endif

            case WC_SIGNATURE_TYPE_NONE:
            default:
                ret = BAD_FUNC_ARG;
                break;
        }
