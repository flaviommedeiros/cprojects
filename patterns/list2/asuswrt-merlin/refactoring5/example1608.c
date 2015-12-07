#ifdef CAN_USE_OPENSSL_CTR
if (should_use_openssl_CTR) {
    if (cipher->using_evp) {
      /* In openssl 1.0.0, there's an if'd out EVP_aes_128_ctr in evp.h.  If
       * it weren't disabled, it might be better just to use that.
       */
      CRYPTO_ctr128_encrypt((const unsigned char *)input,
                            (unsigned char *)output,
                            len,
                            &cipher->key.evp,
                            cipher->ctr_buf.buf,
                            cipher->buf,
                            &cipher->pos,
                            evp_block128_fn);
    } else {
      AES_ctr128_encrypt((const unsigned char *)input,
                         (unsigned char *)output,
                         len,
                         &cipher->key.aes,
                         cipher->ctr_buf.buf,
                         cipher->buf,
                         &cipher->pos);
    }
    return;
  } else
#endif
  {
    int c = cipher->pos;
    if (PREDICT_UNLIKELY(!len)) return;

    while (1) {
      do {
        if (len-- == 0) { cipher->pos = c; return; }
        *(output++) = *(input++) ^ cipher->buf[c];
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
