#ifdef CONFIG_IP_VS_IPV6
if (af == AF_INET6)
		ipv6_hdr(skb)->saddr = cp->vaddr.in6;
	else
#endif
	{
		ip_hdr(skb)->saddr = cp->vaddr.ip;
		ip_send_check(ip_hdr(skb));
	}
