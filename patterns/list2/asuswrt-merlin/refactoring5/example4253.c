#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(authtype, HMACMD5Auth))
        HMAC(EVP_md5(), key, keylen, message, msglen, buf, &buf_len);
    else
#endif
        if (ISTRANSFORM(authtype, HMACSHA1Auth))
        HMAC(EVP_sha1(), key, keylen, message, msglen, buf, &buf_len);
    else {
        QUITFUN(SNMPERR_GENERR, sc_generate_keyed_hash_quit);
    }
