#ifdef CONFIG_IP_VS_IPV6
if (udest->af == AF_INET6) {
		atype = ipv6_addr_type(&udest->addr.in6);
		if ((!(atype & IPV6_ADDR_UNICAST) ||
			atype & IPV6_ADDR_LINKLOCAL) &&
			!__ip_vs_addr_is_local_v6(svc->ipvs->net, &udest->addr.in6))
			return -EINVAL;
	} else
#endif
	{
		atype = inet_addr_type(svc->ipvs->net, udest->addr.ip);
		if (atype != RTN_LOCAL && atype != RTN_UNICAST)
			return -EINVAL;
	}
