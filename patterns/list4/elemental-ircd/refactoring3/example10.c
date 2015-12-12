switch (af) {
    case AF_INET:
        return (inet_ntop4(src, dst, size));
#ifdef RB_IPV6
    case AF_INET6:
        if(IN6_IS_ADDR_V4MAPPED((const struct in6_addr *)src) ||
           IN6_IS_ADDR_V4COMPAT((const struct in6_addr *)src))
            return (inet_ntop4
                    ((const unsigned char *)&((const struct in6_addr *)src)->
                     s6_addr[12], dst, size));
        else
            return (inet_ntop6(src, dst, size));


#endif
    default:
        return (NULL);
    }
