if ((udp_listen==0)
#ifdef USE_TCP
			&& (tcp_listen==0)
#ifdef USE_TLS
			&& (tls_listen==0)
#endif
#endif
#ifdef USE_SCTP
			&& (sctp_listen==0)
#endif
		){
		/* get all listening ipv4/ipv6 interfaces */
		if ( ( (add_interfaces(0, AF_INET, 0,  PROTO_UDP, &ai_lst)==0)
#ifdef __OS_linux
		&&  (!auto_bind_ipv6 || add_interfaces_via_netlink(0, AF_INET6, 0, PROTO_UDP, &ai_lst) == 0)
#else
		&& ( !auto_bind_ipv6 || add_interfaces(0, AF_INET6, 0,  PROTO_UDP, &ai_lst) ==0 ) /* add_interface does not work for IPv6 on Linux */
#endif /* __OS_linux */
			 ) && (addr_info_to_si_lst(ai_lst, 0, PROTO_UDP, 0, &udp_listen)==0)){
			free_addr_info_lst(&ai_lst);
			ai_lst=0;
			/* if ok, try to add the others too */
#ifdef USE_TCP
			if (!tcp_disable){
				if ( ((add_interfaces(0, AF_INET, 0,  PROTO_TCP, &ai_lst)!=0)
#ifdef __OS_linux
    				|| (auto_bind_ipv6 && add_interfaces_via_netlink(0, AF_INET6, 0, PROTO_TCP, &ai_lst) != 0)
#else
				|| (auto_bind_ipv6 && add_interfaces(0, AF_INET6, 0,  PROTO_TCP, &ai_lst) !=0 )
#endif /* __OS_linux */
				) || (addr_info_to_si_lst(ai_lst, 0, PROTO_TCP, 0,
										 				&tcp_listen)!=0))
					goto error;
				free_addr_info_lst(&ai_lst);
				ai_lst=0;
#ifdef USE_TLS
				if (!tls_disable){
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
				}
				free_addr_info_lst(&ai_lst);
				ai_lst=0;
#endif
			}
#endif
#ifdef USE_SCTP
			if (!sctp_disable){
				if (((add_interfaces(0, AF_INET, 0,  PROTO_SCTP, &ai_lst)!=0)
#ifdef __OS_linux
    				|| (auto_bind_ipv6 && add_interfaces_via_netlink(0, AF_INET6, 0, PROTO_SCTP, &ai_lst) != 0)
#else
				|| (auto_bind_ipv6 && add_interfaces(0, AF_INET6, 0,  PROTO_SCTP, &ai_lst) != 0)
#endif /* __OS_linux */
					) || (addr_info_to_si_lst(ai_lst, 0, PROTO_SCTP, 0,
							 				&sctp_listen)!=0))
					goto error;
				free_addr_info_lst(&ai_lst);
				ai_lst=0;
			}
#endif /* USE_SCTP */
		}else{
			/* if error fall back to get hostname */
			/* get our address, only the first one */
			if (uname (&myname) <0){
				LM_ERR("cannot determine hostname, try -l address\n");
				goto error;
			}
			if (add_listen_iface(myname.nodename, 0, 0, 0, 0)!=0){
				LM_ERR("add_listen_iface failed \n");
				goto error;
			}
		}
	}
