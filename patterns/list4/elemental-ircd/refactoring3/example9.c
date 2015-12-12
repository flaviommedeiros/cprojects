switch (src->sa_family) {
    case AF_INET:
        return (rb_inet_ntop(AF_INET, &((struct sockaddr_in *)src)->sin_addr, dst, size));
        break;
#ifdef RB_IPV6
    case AF_INET6:
        return (rb_inet_ntop
                (AF_INET6, &((struct sockaddr_in6 *)src)->sin6_addr, dst, size));
        break;
#endif
    default:
        return NULL;
        break;
    }
