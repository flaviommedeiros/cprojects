if ((fd = socket(PF_INET6, SOCK_RAW, IPPROTO_ICMPV6)) == -1 ||
      getsockopt(fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &hop_limit, &len) ||
#if defined(IPV6_TCLASS) && defined(IPTOS_CLASS_CS6)
      setsockopt(fd, IPPROTO_IPV6, IPV6_TCLASS, &class, sizeof(class)) == -1 ||
#endif
      !fix_fd(fd) ||
      !set_ipv6pktinfo(fd) ||
      setsockopt(fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &val, sizeof(val)) ||
      setsockopt(fd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &val, sizeof(val)) ||
      setsockopt(fd, IPPROTO_ICMPV6, ICMP6_FILTER, &filter, sizeof(filter)) == -1)
    die (_("cannot create ICMPv6 socket: %s"), NULL, EC_BADNET);
