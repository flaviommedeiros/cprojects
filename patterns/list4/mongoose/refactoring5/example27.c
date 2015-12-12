#ifdef MG_ENABLE_SSL
if (conn->ssl != NULL) {
    if (conn->flags & MG_F_SSL_HANDSHAKE_DONE) {
      /* SSL library may have more bytes ready to read then we ask to read.
       * Therefore, read in a loop until we read everything. Without the loop,
       * we skip to the next select() cycle which can just timeout. */
      while ((n = SSL_read(conn->ssl, buf, MG_TCP_RECV_BUFFER_SIZE)) > 0) {
        DBG(("%p %d bytes <- %d (SSL)", conn, n, conn->sock));
        mg_if_recv_tcp_cb(conn, buf, n);
        buf = NULL;
        if (conn->flags & MG_F_CLOSE_IMMEDIATELY) break;
        /* buf has been freed, we need a new one. */
        buf = (char *) MG_MALLOC(MG_TCP_RECV_BUFFER_SIZE);
        if (buf == NULL) break;
      }
      MG_FREE(buf);
      mg_ssl_err(conn, n);
    } else {
      MG_FREE(buf);
      mg_ssl_begin(conn);
      return;
    }
  } else
#endif
  {
    n = (int) MG_RECV_FUNC(conn->sock, buf,
                           recv_avail_size(conn, MG_TCP_RECV_BUFFER_SIZE), 0);
    if (n > 0) {
      DBG(("%p %d bytes (PLAIN) <- %d", conn, n, conn->sock));
      mg_if_recv_tcp_cb(conn, buf, n);
    } else {
      MG_FREE(buf);
    }
    if (mg_is_error(n)) {
      conn->flags |= MG_F_CLOSE_IMMEDIATELY;
    }
  }
