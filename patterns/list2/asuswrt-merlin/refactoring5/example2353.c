#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6)
		ipv6_addr_prefix(&snet.in6, &iph.saddr.in6, svc->netmask);
	else
#endif
		snet.ip = iph.saddr.ip & svc->netmask;
