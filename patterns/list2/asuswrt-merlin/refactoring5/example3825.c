#ifdef CONFIG_IP_VS_IPV6
if (skb->protocol == htons(ETH_P_IPV6))
		ah_esp_debug_packet_v6(pp, skb, offset, msg);
	else
#endif
		ah_esp_debug_packet_v4(pp, skb, offset, msg);
