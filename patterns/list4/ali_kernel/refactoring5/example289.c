#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6) {
		if (__ip_vs_addr_is_local_v6(&udest->addr.in6)) {
			conn_flags = (conn_flags & ~IP_VS_CONN_F_FWD_MASK)
				| IP_VS_CONN_F_LOCALNODE;
		}
	} else
#endif
		if (inet_addr_type(&init_net, udest->addr.ip) == RTN_LOCAL) {
			conn_flags = (conn_flags & ~IP_VS_CONN_F_FWD_MASK)
				| IP_VS_CONN_F_LOCALNODE;
		}
