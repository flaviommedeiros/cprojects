#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (ip6_route_me_harder(skb) != 0)
			goto drop;
	} else
#endif
		if (ip_route_me_harder(skb, RTN_LOCAL) != 0)
			goto drop;
