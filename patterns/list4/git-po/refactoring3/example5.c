switch (af) {
        case AF_INET:
                return (inet_pton4(src, dst));
#ifndef NO_IPV6
        case AF_INET6:
                return (inet_pton6(src, dst));
#endif
        default:
                errno = EAFNOSUPPORT;
                return (-1);
        }
