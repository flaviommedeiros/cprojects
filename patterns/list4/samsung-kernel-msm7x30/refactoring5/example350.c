#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (unlikely(iph.protocol == IPPROTO_ICMPV6)) {
			int related;
			int verdict = ip_vs_in_icmp_v6(skb, &related, hooknum);

			if (related)
				return verdict;
			ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
		}
	} else
#endif
		if (unlikely(iph.protocol == IPPROTO_ICMP)) {
			int related;
			int verdict = ip_vs_in_icmp(skb, &related, hooknum);

			if (related)
				return verdict;
			ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
		}
