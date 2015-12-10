#ifdef USE_UNIX_SOCKETS
if(data->set.str[STRING_UNIX_SOCKET_PATH]) {
      /* Unix domain sockets are local. The host gets ignored, just use the
       * specified domain socket address. Do not cache "DNS entries". There is
       * no DNS involved and we already have the filesystem path available */
      const char *path = data->set.str[STRING_UNIX_SOCKET_PATH];

      hostaddr = calloc(1, sizeof(struct Curl_dns_entry));
      if(!hostaddr)
        result = CURLE_OUT_OF_MEMORY;
      else if((hostaddr->addr = Curl_unix2addr(path)) != NULL)
        hostaddr->inuse++;
      else {
        /* Long paths are not supported for now */
        if(strlen(path) >= sizeof(((struct sockaddr_un *)0)->sun_path)) {
          failf(data, "Unix socket path too long: '%s'", path);
          result = CURLE_COULDNT_RESOLVE_HOST;
        }
        else
          result = CURLE_OUT_OF_MEMORY;
        free(hostaddr);
        hostaddr = NULL;
      }
    }
    else
#endif
    if(!conn->proxy.name || !*conn->proxy.name) {
      /* If not connecting via a proxy, extract the port from the URL, if it is
       * there, thus overriding any defaults that might have been set above. */
      conn->port =  conn->remote_port; /* it is the same port */

      /* Resolve target host right on */
      rc = Curl_resolv_timeout(conn, conn->host.name, (int)conn->port,
                               &hostaddr, timeout_ms);
      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve host '%s'", conn->host.dispname);
        result =  CURLE_COULDNT_RESOLVE_HOST;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
    else {
      /* This is a proxy that hasn't been resolved yet. */

      /* IDN-fix the proxy name */
      fix_hostname(data, conn, &conn->proxy);

      /* resolve proxy */
      rc = Curl_resolv_timeout(conn, conn->proxy.name, (int)conn->port,
                               &hostaddr, timeout_ms);

      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(rc == CURLRESOLV_TIMEDOUT)
        result = CURLE_OPERATION_TIMEDOUT;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve proxy '%s'", conn->proxy.dispname);
        result = CURLE_COULDNT_RESOLVE_PROXY;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
