#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (unlikely(iph.protocol == IPPROTO_ICMPV6)) {
			int related;
			int verdict = ip_vs_in_icmp_v6(ipvs, skb, &related,
						       hooknum, &iph);

			if (related)
				return verdict;
		}
	} else
#endif
		if (unlikely(iph.protocol == IPPROTO_ICMP)) {
			int related;
			int verdict = ip_vs_in_icmp(ipvs, skb, &related,
						    hooknum);

			if (related)
				return verdict;
		}
