#ifdef OPENSSL_FIPS
if (!FIPS_module_mode_set(r, FIPS_AUTH_USER_PASS))
        return 0;
