#ifdef RB_IPV6
if(client_p->localClient->ip.ss_family == AF_INET6)
        port = ntohs(((struct sockaddr_in6 *)&client_p->localClient->ip)->sin6_port);
    else
#endif
        port = ntohs(((struct sockaddr_in *)&client_p->localClient->ip)->sin_port);
