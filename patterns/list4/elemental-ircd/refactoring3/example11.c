switch (af) {
    case AF_INET:
        return (inet_pton4(src, dst));
#ifdef RB_IPV6
    case AF_INET6:
        /* Somebody might have passed as an IPv4 address this is sick but it works */
        if(inet_pton4(src, dst)) {
            char tmp[HOSTIPLEN];
            sprintf(tmp, "::ffff:%s", src);
            return (inet_pton6(tmp, dst));
        } else
            return (inet_pton6(src, dst));
#endif
    default:
        return (-1);
    }
