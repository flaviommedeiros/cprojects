#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (sysctl_snat_reroute(skb) && ip6_route_me_harder(skb) != 0)
			return 1;
	} else
#endif
		if ((sysctl_snat_reroute(skb) ||
		     skb_rtable(skb)->rt_flags & RTCF_LOCAL) &&
		    ip_route_me_harder(skb, RTN_LOCAL) != 0)
			return 1;
