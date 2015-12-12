#ifndef MONGOOSE_NO_WEBSOCKET
if (conn->mg_conn.is_websocket) {
    do { } while (deliver_websocket_frame(conn));
  } else
#endif
  if (conn->num_bytes_recv >= (conn->cl + conn->request_len) &&
      call_request_handler(conn) == MG_FALSE) {
    open_local_endpoint(conn, 1);
  }
