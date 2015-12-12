switch (srv->ss_family) {
#ifdef RB_IPV6
        case AF_INET6:
            if (srv->ss_family == inp->ss_family)
                if (v6->sin6_port == v6in->sin6_port)
                    if ((memcmp(&v6->sin6_addr.s6_addr, &v6in->sin6_addr.s6_addr,
                                sizeof(struct in6_addr)) == 0) ||
                        (memcmp(&v6->sin6_addr.s6_addr, &in6addr_any,
                                sizeof(struct in6_addr)) == 0)) {
                        ns_timeout_count[ns] = 0;
                        return 1;
                    }
            break;
#endif
        case AF_INET:
            if (srv->ss_family == inp->ss_family)
                if (v4->sin_port == v4in->sin_port)
                    if ((v4->sin_addr.s_addr == INADDR_ANY)
                        || (v4->sin_addr.s_addr == v4in->sin_addr.s_addr)) {
                        ns_timeout_count[ns] = 0;
                        return 1;
                    }
            break;
        default:
            break;
        }
