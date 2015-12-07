#ifdef CAN_USE_OPENSSL_CTR
if (should_use_openssl_CTR)
    memset(cipher->buf, 0, sizeof(cipher->buf));
  else
#endif
    aes_fill_buf_(cipher);
