if((0 == Curl_inet_pton(AF_INET, conn->host.name, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, conn->host.name, &addr)) &&
#endif
     data->set.ssl.verifyhost) {
    err = SSLSetPeerDomainName(connssl->ssl_ctx, conn->host.name,
                               strlen(conn->host.name));
    if(err != noErr) {
      infof(data, "WARNING: SSL: SSLSetPeerDomainName() failed: OSStatus %d\n",
            err);
    }
  }
