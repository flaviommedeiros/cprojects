#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth)) {
        return BYTESIZE(SNMP_TRANS_AUTHLEN_HMACMD5);
    } else
#endif
        if (ISTRANSFORM(hashtype, HMACSHA1Auth)) {
        return BYTESIZE(SNMP_TRANS_AUTHLEN_HMACSHA1);
    }
