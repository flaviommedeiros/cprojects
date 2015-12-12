#ifdef RB_IPV6
if(reply->addr.ss_family == AF_INET6)
        ((struct sockaddr_in6 *)&client_p->localClient->ip)->sin6_port = port;
    else
#endif
        ((struct sockaddr_in *)&client_p->localClient->ip)->sin_port = port;
