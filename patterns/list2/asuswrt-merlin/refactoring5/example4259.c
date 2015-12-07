#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth))
        EVP_DigestInit(ctx, EVP_md5());
    else
#endif
        if (ISTRANSFORM(hashtype, HMACSHA1Auth))
        EVP_DigestInit(ctx, EVP_sha1());
    else
        QUITFUN(SNMPERR_GENERR, generate_Ku_quit);
