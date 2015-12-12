#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
		if (ipv6_hdr(skb)->nexthdr == IPPROTO_FRAGMENT) {
			if (ip_vs_gather_frags_v6(skb,
						  ip_vs_defrag_user(hooknum)))
				return NF_STOLEN;
		}

		ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
	} else
#endif
		if (unlikely(ip_is_fragment(ip_hdr(skb)) && !pp->dont_defrag)) {
			if (ip_vs_gather_frags(skb,
					       ip_vs_defrag_user(hooknum)))
				return NF_STOLEN;

			ip_vs_fill_iphdr(af, skb_network_header(skb), &iph);
		}
