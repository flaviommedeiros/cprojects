#ifdef RB_IPV6
if(localaddr.ss_family == AF_INET6) {
        auth->lport = ntohs(((struct sockaddr_in6 *)&localaddr)->sin6_port);
        ((struct sockaddr_in6 *)&localaddr)->sin6_port = 0;
    } else
#endif
    {
        auth->lport = ntohs(((struct sockaddr_in *)&localaddr)->sin_port);
        ((struct sockaddr_in *)&localaddr)->sin_port = 0;
    }
