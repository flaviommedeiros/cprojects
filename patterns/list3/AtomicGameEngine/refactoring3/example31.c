switch(conn->proxytype) {
#ifndef CURL_DISABLE_PROXY
  case CURLPROXY_SOCKS5:
  case CURLPROXY_SOCKS5_HOSTNAME:
    return Curl_SOCKS5(conn->proxyuser, conn->proxypasswd,
                       conn->host.name, conn->remote_port,
                       FIRSTSOCKET, conn);

  case CURLPROXY_SOCKS4:
    return Curl_SOCKS4(conn->proxyuser, conn->host.name,
                       conn->remote_port, FIRSTSOCKET, conn, FALSE);

  case CURLPROXY_SOCKS4A:
    return Curl_SOCKS4(conn->proxyuser, conn->host.name,
                       conn->remote_port, FIRSTSOCKET, conn, TRUE);

#endif /* CURL_DISABLE_PROXY */
  case CURLPROXY_HTTP:
  case CURLPROXY_HTTP_1_0:
    /* do nothing here. handled later. */
    break;
  default:
    break;
  }
