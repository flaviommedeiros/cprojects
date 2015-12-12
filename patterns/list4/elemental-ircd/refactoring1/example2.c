if(rb_inet_pton(AF_INET, src, &((struct sockaddr_in *)dst)->sin_addr)) {
        ((struct sockaddr_in *)dst)->sin_port = 0;
        ((struct sockaddr_in *)dst)->sin_family = AF_INET;
        SET_SS_LEN(dst, sizeof(struct sockaddr_in));
        return 1;
    }
#ifdef RB_IPV6
    else if(rb_inet_pton(AF_INET6, src, &((struct sockaddr_in6 *)dst)->sin6_addr)) {
        ((struct sockaddr_in6 *)dst)->sin6_port = 0;
        ((struct sockaddr_in6 *)dst)->sin6_family = AF_INET6;
        SET_SS_LEN(dst, sizeof(struct sockaddr_in6));
        return 1;
    }
#endif
