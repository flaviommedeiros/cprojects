if(!Curl_inet_pton(AF_INET, conn->host.name, &addr) &&
#ifdef ENABLE_IPV6
     !Curl_inet_pton(AF_INET6, conn->host.name, &addr) &&
#endif
     sni && ssl_set_hostname(&connssl->ssl, conn->host.name)) {
     infof(data, "WARNING: failed to configure "
                 "server name indication (SNI) TLS extension\n");
  }
