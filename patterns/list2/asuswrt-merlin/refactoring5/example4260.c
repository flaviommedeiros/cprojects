#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth)) {
        MD5_Init(&cmd5);
        cryptotype = TYPE_MD5;
    } else
#endif
           if (ISTRANSFORM(hashtype, HMACSHA1Auth)) {
        SHA1_Init(&csha1);
        cryptotype = TYPE_SHA1;
    } else {
        return (SNMPERR_GENERR);
    }
