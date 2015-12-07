#if !defined(OPENSSL_NO_RSA) || !defined(OPENSSL_NO_DSA) || !defined(OPENSSL_NO_ECDSA)
if (nocert)
#endif
    {
        s_cert_file = NULL;
        s_key_file = NULL;
        s_dcert_file = NULL;
        s_dkey_file = NULL;
#ifndef OPENSSL_NO_TLSEXT
        s_cert_file2 = NULL;
        s_key_file2 = NULL;
#endif
    }
