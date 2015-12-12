#ifdef CONFIG_IP_VS_IPV6
if (cp->daf == AF_INET6)
			snprintf(dbuf, sizeof(dbuf), "%pI6", &cp->daddr.in6);
		else
#endif
			snprintf(dbuf, sizeof(dbuf), "%08X",
				 ntohl(cp->daddr.ip));
