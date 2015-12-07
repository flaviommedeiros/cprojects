#ifdef ENABLE_IPV6
if(conn->bits.ipv6_ip &&
     Curl_inet_pton(AF_INET6, conn->host.name, &addr)) {
    target = GEN_IPADD;
    addrlen = sizeof(struct in6_addr);
  }
  else
#endif
    if(Curl_inet_pton(AF_INET, conn->host.name, &addr)) {
      target = GEN_IPADD;
      addrlen = sizeof(struct in_addr);
    }
