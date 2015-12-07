#ifdef V2_HANDSHAKE_SERVER
if (isServer) {
    SSL_set_info_callback(result->ssl, tor_tls_server_info_callback);
  } else
#endif
  {
    SSL_set_info_callback(result->ssl, tor_tls_debug_state_callback);
  }
