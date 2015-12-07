# ifdef OPENSSL_FIPS
if (FIPS_mode())
        cert_pbe = NID_pbe_WithSHA1And3_Key_TripleDES_CBC;
    else
# endif
        cert_pbe = NID_pbe_WithSHA1And40BitRC2_CBC;
