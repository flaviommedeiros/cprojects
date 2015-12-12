#ifdef CONFIG_IP_VS_IPV6
if (skb_af == AF_INET6) {
		int addr_type = ipv6_addr_type(&ipv6_hdr(skb)->saddr);

		source_is_loopback =
			(!skb->dev || skb->dev->flags & IFF_LOOPBACK) &&
			(addr_type & IPV6_ADDR_LOOPBACK);
		old_rt_is_local = __ip_vs_is_local_route6(
			(struct rt6_info *)skb_dst(skb));
	} else
#endif
	{
		source_is_loopback = ipv4_is_loopback(ip_hdr(skb)->saddr);
		old_rt_is_local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	}
