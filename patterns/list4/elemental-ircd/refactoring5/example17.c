#ifdef RB_IPV6
if(source_p->localClient->ip.ss_family == AF_INET6)
            port = ntohs(((struct sockaddr_in6 *)&source_p->localClient->listener->addr)->sin6_port);
        else
#endif
            port = ntohs(((struct sockaddr_in *)&source_p->localClient->listener->addr)->sin_port);
