#ifdef RB_IPV6
if(localaddr.ss_family == AF_INET6) {
        auth->rport = ntohs(((struct sockaddr_in6 *)&destaddr)->sin6_port);
        ((struct sockaddr_in6 *)&destaddr)->sin6_port = htons(113);
    } else
#endif
    {
        auth->rport = ntohs(((struct sockaddr_in *)&destaddr)->sin_port);
        ((struct sockaddr_in *)&destaddr)->sin_port = htons(113);
    }
