#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET)
#endif
		if (unlikely(ip_is_fragment(ip_hdr(skb)) && !pp->dont_defrag)) {
			if (ip_vs_gather_frags(skb,
					       ip_vs_defrag_user(hooknum)))
				return NF_STOLEN;

			ip_vs_fill_ip4hdr(skb_network_header(skb), &iph);
		}
