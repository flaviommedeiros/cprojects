if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
     sni &&
     !SSL_set_tlsext_host_name(connssl->handle, conn->host.name))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n");
