#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (unlikely(iph.protocol == IPPROTO_ICMPV6)) {
			int related, verdict = ip_vs_out_icmp_v6(skb, &related);

			if (related)
				return verdict;

			ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
		}
	} else
#endif
		if (unlikely(ip_hdr(skb)->frag_off & htons(IP_MF|IP_OFFSET) &&
			     !pp->dont_defrag)) {
			if (ip_vs_gather_frags(skb, IP_DEFRAG_VS_OUT))
				return NF_STOLEN;

			ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
		}
