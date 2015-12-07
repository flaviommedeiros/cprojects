#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(authtype, HMACMD5Auth)) {
	if (pkcs_sign(CKM_MD5_HMAC,key, keylen, message,
			msglen, buf, &buf_len) != SNMPERR_SUCCESS) {
            QUITFUN(SNMPERR_GENERR, sc_generate_keyed_hash_quit);
        }
    } else
#endif
        if (ISTRANSFORM(authtype, HMACSHA1Auth)) {
	if (pkcs_sign(CKM_SHA_1_HMAC,key, keylen, message,
			msglen, buf, &buf_len) != SNMPERR_SUCCESS) {
            QUITFUN(SNMPERR_GENERR, sc_generate_keyed_hash_quit);
        }
    } else {
        QUITFUN(SNMPERR_GENERR, sc_generate_keyed_hash_quit);
    }
