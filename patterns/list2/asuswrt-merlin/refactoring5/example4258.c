#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth)) {
	rval = pkcs_digest(CKM_MD5, buf, buf_len, MAC, &tmp_len);
        *MAC_len = tmp_len;
    } else
#endif
        if (ISTRANSFORM(hashtype, HMACSHA1Auth)) {
	rval = pkcs_digest(CKM_SHA_1, buf, buf_len, MAC, &tmp_len);
        *MAC_len = tmp_len;
    } else {
        return (SNMPERR_GENERR);
    }
