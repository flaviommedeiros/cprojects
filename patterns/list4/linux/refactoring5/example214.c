#ifdef CONFIG_IP_VS_IPV6
if (p->af == AF_INET6)
		ip_vs_bind_xmit_v6(cp);
	else
#endif
		ip_vs_bind_xmit(cp);
