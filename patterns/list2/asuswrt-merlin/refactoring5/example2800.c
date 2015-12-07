#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth)) {
        hashfn = (const EVP_MD *) EVP_md5();
    } else
#endif
        if (ISTRANSFORM(hashtype, HMACSHA1Auth)) {
        hashfn = (const EVP_MD *) EVP_sha1();
    } else {
        return (SNMPERR_GENERR);
    }
