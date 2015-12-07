if (((add_interfaces(0, AF_INET, 0, PROTO_TLS,
										&ai_lst)!=0)
#ifdef __OS_linux
    				|| (auto_bind_ipv6 && add_interfaces_via_netlink(0, AF_INET6, 0, PROTO_TLS, &ai_lst) != 0)
#else
				|| (auto_bind_ipv6 && add_interfaces(0, AF_INET6, 0,  PROTO_TLS, &ai_lst)!=0)
#endif /* __OS_linux */
					) || (addr_info_to_si_lst(ai_lst, 0, PROTO_TLS, 0,
										 				&tls_listen)!=0))
						goto error;
