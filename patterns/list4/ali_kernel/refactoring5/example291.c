#ifdef CONFIG_IP_VS_IPV6
if (svc->af == AF_INET6)
				seq_printf(seq, "%s  [%pI6]:%04X %s%s ",
					   ip_vs_proto_name(svc->protocol),
					   &svc->addr.in6,
					   ntohs(svc->port),
					   svc->scheduler->name,
					   (svc->flags & IP_VS_SVC_F_ONEPACKET)?
					   " ops":"");
			else
#endif
				seq_printf(seq, "%s  %08X:%04X %s%s ",
					   ip_vs_proto_name(svc->protocol),
					   ntohl(svc->addr.ip),
					   ntohs(svc->port),
					   svc->scheduler->name,
					   (svc->flags & IP_VS_SVC_F_ONEPACKET)?
					   " ops":"");
