#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6)
		unicast = ipv6_addr_type(&iph.daddr.in6) & IPV6_ADDR_UNICAST;
	else
#endif
		unicast = (inet_addr_type(net, iph.daddr.ip) == RTN_UNICAST);
