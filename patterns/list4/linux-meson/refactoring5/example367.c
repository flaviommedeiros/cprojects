#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
		sctphoff = sizeof(struct ipv6hdr);
	else
#endif
		sctphoff = ip_hdrlen(skb);
