#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		struct dst_entry *dst = skb_dst(skb);

		if (dst->dev && !(dst->dev->flags & IFF_LOOPBACK) &&
		    ip6_route_me_harder(skb) != 0)
			return 1;
	} else
#endif
		if (!(skb_rtable(skb)->rt_flags & RTCF_LOCAL) &&
		    ip_route_me_harder(skb, RTN_LOCAL) != 0)
			return 1;
