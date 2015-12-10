switch(state) {
    case SSL_NEXT_PROTO_NO_SUPPORT:
    case SSL_NEXT_PROTO_NO_OVERLAP:
      if(connssl->asked_for_h2)
        infof(conn->data, "TLS, neither ALPN nor NPN succeeded\n");
      return;
#ifdef SSL_ENABLE_ALPN
    case SSL_NEXT_PROTO_SELECTED:
      infof(conn->data, "ALPN, server accepted to use %.*s\n", buflen, buf);
      break;
#endif
    case SSL_NEXT_PROTO_NEGOTIATED:
      infof(conn->data, "NPN, server accepted to use %.*s\n", buflen, buf);
      break;
    }
