#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth))
        return pkcs_generate_Ku(CKM_MD5, P, pplen, Ku, kulen);
    else
#endif
        if (ISTRANSFORM(hashtype, HMACSHA1Auth))
        return pkcs_generate_Ku(CKM_SHA_1, P, pplen, Ku, kulen);
    else {
        return (SNMPERR_GENERR);
    }
