switch(family) {
    case AF_INET:
        SET_SS_LEN(&vaddr, sizeof(struct sockaddr_in));
        ((struct sockaddr_in *)&vaddr)->sin_port = htons(port);
        break;
#ifdef RB_IPV6
    case AF_INET6:
        SET_SS_LEN(&vaddr, sizeof(struct sockaddr_in6));
        ((struct sockaddr_in6 *)&vaddr)->sin6_port = htons(port);
        break;
#endif
    default:
        break;
    }
