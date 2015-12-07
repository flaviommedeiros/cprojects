if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
     sni &&
     (gnutls_server_name_set(session, GNUTLS_NAME_DNS, conn->host.name,
                             strlen(conn->host.name)) < 0))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n");
