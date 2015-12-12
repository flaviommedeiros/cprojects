#ifdef HAVE_ECC
if (ssl->options.cipherSuite0 == ECC_BYTE &&
                     ssl->specs.sig_algo == ecc_dsa_sa_algo) {
        output[i++] = ecdsa_sign;
    } else
#endif /* HAVE_ECC */
    {
        output[i++] = rsa_sign;
    }
