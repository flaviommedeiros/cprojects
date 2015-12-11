if (first->protocol == htons(ETH_P_IP)) {
		struct iphdr *iph = ip_hdr(skb);
		iph->tot_len = 0;
		iph->check = 0;
		tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr,
							 iph->daddr, 0,
							 IPPROTO_TCP,
							 0);
		type_tucmd |= E1000_ADVTXD_TUCMD_IPV4;
		first->tx_flags |= IGB_TX_FLAGS_TSO |
				   IGB_TX_FLAGS_CSUM |
				   IGB_TX_FLAGS_IPV4;
#ifdef NETIF_F_TSO6
	} else if (skb_is_gso_v6(skb)) {
		ipv6_hdr(skb)->payload_len = 0;
		tcp_hdr(skb)->check = ~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						       &ipv6_hdr(skb)->daddr,
						       0, IPPROTO_TCP, 0);
		first->tx_flags |= IGB_TX_FLAGS_TSO |
				   IGB_TX_FLAGS_CSUM;
#endif
	}
#endif
