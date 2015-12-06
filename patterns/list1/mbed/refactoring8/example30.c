const uint8_t ssl_prot_prefs[NUM_PROTOCOLS] = 
#ifdef CONFIG_SSL_PROT_LOW                  /* low security, fast speed */
{ SSL_RC4_128_SHA, SSL_AES128_SHA, SSL_AES256_SHA, SSL_RC4_128_MD5 };
