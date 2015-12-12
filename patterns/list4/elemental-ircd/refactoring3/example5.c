switch(family) {
        case AF_INET:
            ((struct sockaddr_in *)&vaddr)->sin_addr.s_addr = INADDR_ANY;
            break;
#ifdef RB_IPV6
        case AF_INET6:
            memcpy(&((struct sockaddr_in6 *)&vaddr)->sin6_addr, &in6addr_any, sizeof(struct in6_addr));
            break;
        default:
            return;
#endif
        }
