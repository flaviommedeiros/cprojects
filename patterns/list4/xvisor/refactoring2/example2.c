#if LWIP_TCP
if (conn->type == NETCONN_TCP)
#endif /* (LWIP_UDP || LWIP_RAW) */
  {
    if (!netconn_get_noautorecved(conn) || (buf == NULL)) {
      /* Let the stack know that we have taken the data. */
      /* TODO: Speedup: Don't block and wait for the answer here
         (to prevent multiple thread-switches). */
      msg.function = do_recv;
      msg.msg.conn = conn;
      if (buf != NULL) {
        msg.msg.msg.r.len = ((struct pbuf *)buf)->tot_len;
      } else {
        msg.msg.msg.r.len = 1;
      }
      /* don't care for the return value of do_recv */
      TCPIP_APIMSG(&msg);
    }

    /* If we are closed, we indicate that we no longer wish to use the socket */
    if (buf == NULL) {
      API_EVENT(conn, NETCONN_EVT_RCVMINUS, 0);
      /* Avoid to lose any previous error code */
      NETCONN_SET_SAFE_ERR(conn, ERR_CLSD);
      return ERR_CLSD;
    }
    len = ((struct pbuf *)buf)->tot_len;
  }
#endif /* LWIP_TCP */
#if LWIP_TCP && (LWIP_UDP || LWIP_RAW)
  else
#endif /* LWIP_TCP && (LWIP_UDP || LWIP_RAW) */
#if (LWIP_UDP || LWIP_RAW)
  {
    LWIP_ASSERT("buf != NULL", buf != NULL);
    len = netbuf_len((struct netbuf *)buf);
  }
