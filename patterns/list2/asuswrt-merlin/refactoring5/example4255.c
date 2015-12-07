#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(authtype, HMACMD5Auth))
        rval = MD5_hmac(message, msglen, MAC, *maclen, key, keylen);
    else
#endif
         if (ISTRANSFORM(authtype, HMACSHA1Auth))
        rval = SHA1_hmac(message, msglen, MAC, *maclen, key, keylen);
    else {
        QUITFUN(SNMPERR_GENERR, sc_generate_keyed_hash_quit);
    }
