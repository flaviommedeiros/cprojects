#ifdef MG_ENABLE_SSL
if (nc->ssl != NULL) {
    if (nc->flags & MG_F_SSL_HANDSHAKE_DONE) {
      n = SSL_write(nc->ssl, io->buf, io->len);
      if (n <= 0) {
        int ssl_err = mg_ssl_err(nc, n);
        if (ssl_err == SSL_ERROR_WANT_READ || ssl_err == SSL_ERROR_WANT_WRITE) {
          return; /* Call us again */
        }
      } else {
        /* Successful SSL operation, clear off SSL wait flags */
        nc->flags &= ~(MG_F_WANT_READ | MG_F_WANT_WRITE);
      }
    } else {
      mg_ssl_begin(nc);
      return;
    }
  } else
#endif
  {
    n = (int) MG_SEND_FUNC(nc->sock, io->buf, io->len, 0);
  }
