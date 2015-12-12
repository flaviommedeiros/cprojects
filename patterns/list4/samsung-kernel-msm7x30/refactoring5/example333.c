#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6) {
				if (csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						    &ipv6_hdr(skb)->daddr,
						    skb->len - udphoff,
						    ipv6_hdr(skb)->nexthdr,
						    skb->csum)) {
					IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
							 "Failed checksum for");
					return 0;
				}
			} else
#endif
				if (csum_tcpudp_magic(ip_hdr(skb)->saddr,
						      ip_hdr(skb)->daddr,
						      skb->len - udphoff,
						      ip_hdr(skb)->protocol,
						      skb->csum)) {
					IP_VS_DBG_RL_PKT(0, af, pp, skb, 0,
							 "Failed checksum for");
					return 0;
				}
