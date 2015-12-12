#ifdef CONFIG_IP_VS_IPV6
if (cp->daf == AF_INET6)
			cp->packet_xmit = ip_vs_tunnel_xmit_v6;
		else
#endif
			cp->packet_xmit = ip_vs_tunnel_xmit;
