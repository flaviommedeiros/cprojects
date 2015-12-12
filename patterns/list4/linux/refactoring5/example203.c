#ifdef CONFIG_IP_VS_IPV6
if (ipvs->bcfg.mcast_af == AF_INET6)
		result = join_mcast_group6(sock->sk, &mcast_addr.in6.sin6_addr,
					   ipvs->bcfg.mcast_ifn);
	else
#endif
		result = join_mcast_group(sock->sk, &mcast_addr.in.sin_addr,
					  ipvs->bcfg.mcast_ifn);
