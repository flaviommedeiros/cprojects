#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
		udphoff = sizeof(struct ipv6hdr);
	else
#endif
		udphoff = ip_hdrlen(skb);
