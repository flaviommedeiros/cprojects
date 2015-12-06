#ifdef NS_ENABLE_SSL
if (conn->ssl != NULL) {
    if (conn->flags & NSF_SSL_HANDSHAKE_DONE) {
      /* SSL library may have more bytes ready to read then we ask to read.
       * Therefore, read in a loop until we read everything. Without the loop,
       * we skip to the next select() cycle which can just timeout. */
      while ((n = SSL_read(conn->ssl, buf, sizeof(buf))) > 0) {
        DBG(("%p %d bytes <- %d (SSL)", conn, n, conn->sock));
        mbuf_append(&conn->recv_mbuf, buf, n);
        ns_call(conn, NS_RECV, &n);
      }
      ns_ssl_err(conn, n);
    } else {
      ns_ssl_begin(conn);
      return;
    }
  } else
#endif
  {
    to_recv = recv_avail_size(conn, sizeof(buf));
    while ((n = (int) NS_RECV_FUNC(conn->sock, buf, to_recv, 0)) > 0) {
      DBG(("%p %d bytes (PLAIN) <- %d", conn, n, conn->sock));
      mbuf_append(&conn->recv_mbuf, buf, n);
      ns_call(conn, NS_RECV, &n);
#ifdef NS_ESP8266
      /*
       * TODO(alashkin): ESP/RTOS recv implementation tend to block
       * even in non-blocking mode, so, break the loop
       * if received size less than buffer size
       * and wait for next select()
       * Some of RTOS specific call missed?
       */
      if (to_recv > n) {
        break;
      }
      to_recv = recv_avail_size(conn, sizeof(buf));
#endif
    }
    DBG(("recv returns %d", n));
  }
