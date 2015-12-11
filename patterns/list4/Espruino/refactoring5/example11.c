#ifdef USE_TLS
if (BITFIELD_GET(socketIsHTTPS, sckt)) {
    SSLSocketData *sd = ssl_getSocketData(sckt);
    if (!sd) return -1;
    if (sd->connecting) return 0; // busy

    int ret = mbedtls_ssl_write( &sd->ssl, buf, len );
    if( ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE )
      return 0;
    return ret;
  } else
#endif
  {
    return net->send(net, sckt, buf, len);
  }
