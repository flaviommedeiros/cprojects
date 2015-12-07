#ifndef NETSNMP_DISABLE_MD5
if (ISTRANSFORM(hashtype, HMACMD5Auth)) {
        if (*MAC_len < MD5_DIGEST_LENGTH)
            return (SNMPERR_GENERR);      /* the buffer isn't big enough */
	MD5_Init(&cmd5);
        MD5_Update(&cmd5, buf, buf_len);
        MD5_Final(MAC, &cmd5);
        *MAC_len = MD5_DIGEST_LENGTH;
    } else 
#endif
    if (ISTRANSFORM(hashtype, HMACSHA1Auth)) {
        if (*MAC_len < SHA_DIGEST_LENGTH)
            return (SNMPERR_GENERR);      /* the buffer isn't big enough */
	SHA1_Init(&csha1);
        SHA1_Update(&csha1, buf, buf_len);
        SHA1_Final(MAC, &csha1);
        *MAC_len = SHA_DIGEST_LENGTH;
            
    } else {
        return (SNMPERR_GENERR);
    }
