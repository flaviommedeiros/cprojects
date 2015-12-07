if(
#ifdef WSAEWOULDBLOCK
      /* This is how Windows does it */
      (WSAEWOULDBLOCK == err)
#else
      /* errno may be EWOULDBLOCK or on some systems EAGAIN when it returned
         due to its inability to send off data without blocking. We therefor
         treat both error codes the same here */
      (EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err)
#endif
      ) {
      /* this is just a case of EWOULDBLOCK */
      *code = CURLE_AGAIN;
    }
    else {
      failf(conn->data, "Recv failure: %s",
            Curl_strerror(conn, err));
      conn->data->state.os_errno = err;
      *code = CURLE_RECV_ERROR;
    }
