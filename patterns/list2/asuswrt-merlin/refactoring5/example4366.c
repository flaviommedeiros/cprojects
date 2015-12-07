#ifdef OPENSSL_FIPS
if (FIPS_mode())
            nid_cert = NID_pbe_WithSHA1And3_Key_TripleDES_CBC;
        else
#endif
#ifdef OPENSSL_NO_RC2
            nid_cert = NID_pbe_WithSHA1And3_Key_TripleDES_CBC;
