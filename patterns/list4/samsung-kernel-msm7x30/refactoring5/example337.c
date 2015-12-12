#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
		ip_vs_tcpudp_debug_packet_v6(pp, skb, offset, msg);
	else
#endif
		ip_vs_tcpudp_debug_packet_v4(pp, skb, offset, msg);
