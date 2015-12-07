if (
#ifdef DISABLE_SSL3_HANDSHAKE
      1 ||
#endif
      SSLeay()  <  OPENSSL_V(0,9,8,'s') ||
      (SSLeay() >= OPENSSL_V_SERIES(0,9,9) &&
       SSLeay() <  OPENSSL_V(1,0,0,'f'))) {
    /* And not SSL3 if it's subject to CVE-2011-4576. */
    log_info(LD_NET, "Disabling SSLv3 because this OpenSSL version "
             "might otherwise be vulnerable to CVE-2011-4576 "
             "(compile-time version %08lx (%s); "
             "runtime version %08lx (%s))",
             (unsigned long)OPENSSL_VERSION_NUMBER, OPENSSL_VERSION_TEXT,
             (unsigned long)SSLeay(), SSLeay_version(SSLEAY_VERSION));
    SSL_CTX_set_options(result->ctx, SSL_OP_NO_SSLv3);
  }
