#ifdef RB_IPV6
if(listener->addr.ss_family == AF_INET6)
        port = ntohs(((const struct sockaddr_in6 *)&listener->addr)->sin6_port);
    else
#endif
        port = ntohs(((const struct sockaddr_in *)&listener->addr)->sin_port);
