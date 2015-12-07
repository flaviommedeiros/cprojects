#ifdef ENABLE_IPV6
if(he->h_addrtype == AF_INET6)
      ss_size = sizeof (struct sockaddr_in6);
    else
#endif
      ss_size = sizeof (struct sockaddr_in);
