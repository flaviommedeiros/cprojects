switch(sig_type) {
#ifdef HAVE_ECC
            case WC_SIGNATURE_TYPE_ECC:
            {

                int is_valid_sig = 0;

                /* Perform verification of signature using provided ECC key */
                ret = wc_ecc_verify_hash(sig, sig_len, hash_data, hash_len, &is_valid_sig, (ecc_key*)key);
                if (ret != 0 || is_valid_sig != 1) {
                    ret = SIG_VERIFY_E;
                }
                break;
            }
#endif
#ifndef NO_RSA
            case WC_SIGNATURE_TYPE_RSA:
            {
                byte *plain_data = (byte*)XMALLOC(hash_len, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                if (plain_data) {
                    /* Perform verification of signature using provided RSA key */
                    ret = wc_RsaSSL_Verify(sig, sig_len, plain_data, hash_len, (RsaKey*)key);
                    if (ret != hash_len || XMEMCMP(plain_data, hash_data, hash_len) != 0) {
                        ret = SIG_VERIFY_E;
                    }
                    XFREE(plain_data, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                }
                else {
                    ret = MEMORY_E;
                }
                break;
            }
#endif

            case WC_SIGNATURE_TYPE_NONE:
            default:
                ret = BAD_FUNC_ARG;
                break;
        }
