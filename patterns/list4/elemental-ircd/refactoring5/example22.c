#ifdef RB_IPV6
if(in->sa_family == AF_INET6)
        ipptr = &((struct sockaddr_in6 *)in)->sin6_addr;
    else
#endif
        ipptr = &((struct sockaddr_in *)in)->sin_addr;
