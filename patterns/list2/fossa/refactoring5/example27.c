#ifdef NS_ENABLE_SSL
if (conn->ssl != NULL) {
    if (conn->flags & NSF_SSL_HANDSHAKE_DONE) {
      n = SSL_write(conn->ssl, io->buf, io->len);
      if (n <= 0) {
        int ssl_err = ns_ssl_err(conn, n);
        if (ssl_err == SSL_ERROR_WANT_READ || ssl_err == SSL_ERROR_WANT_WRITE) {
          return; /* Call us again */
        } else {
          conn->flags |= NSF_CLOSE_IMMEDIATELY;
        }
      } else {
        /* Successful SSL operation, clear off SSL wait flags */
        conn->flags &= ~(NSF_WANT_READ | NSF_WANT_WRITE);
      }
    } else {
      ns_ssl_begin(conn);
      return;
    }
  } else
#endif
  {
    n = (int) NS_SEND_FUNC(conn->sock, io->buf, io->len, 0);
  }
