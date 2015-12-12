#ifdef RB_IPV6
if (strchr(mask, ':') && strchr(address, ':')) {
        aftype = AF_INET6;
        ipptr = &((struct sockaddr_in6 *)&ipaddr)->sin6_addr;
        maskptr = &((struct sockaddr_in6 *)&maskaddr)->sin6_addr;
    } else
#endif
        if (!strchr(mask, ':') && !strchr(address, ':')) {
            aftype = AF_INET;
            ipptr = &((struct sockaddr_in *)&ipaddr)->sin_addr;
            maskptr = &((struct sockaddr_in *)&maskaddr)->sin_addr;
        } else
            return 0;
