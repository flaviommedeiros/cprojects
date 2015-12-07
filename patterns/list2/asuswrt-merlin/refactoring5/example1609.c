#ifdef CAN_USE_OPENSSL_CTR
if (should_use_openssl_CTR) {
    aes_crypt(cipher, data, len, data);
    return;
  } else
#endif
  {
    int c = cipher->pos;
    if (PREDICT_UNLIKELY(!len)) return;

    while (1) {
      do {
        if (len-- == 0) { cipher->pos = c; return; }
        *(data++) ^= cipher->buf[c];
      } while (++c != 16);
      cipher->pos = c = 0;
      if (PREDICT_UNLIKELY(! ++COUNTER(cipher, 0))) {
        if (PREDICT_UNLIKELY(! ++COUNTER(cipher, 1))) {
          if (PREDICT_UNLIKELY(! ++COUNTER(cipher, 2))) {
            ++COUNTER(cipher, 3);
            UPDATE_CTR_BUF(cipher, 3);
          }
          UPDATE_CTR_BUF(cipher, 2);
        }
        UPDATE_CTR_BUF(cipher, 1);
      }
      UPDATE_CTR_BUF(cipher, 0);
      aes_fill_buf_(cipher);
    }
  }
