#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6)
		ipv6_addr_prefix(&snet.in6, &src_addr->in6,
				 (__force __u32) svc->netmask);
	else
#endif
		snet.ip = src_addr->ip & svc->netmask;
