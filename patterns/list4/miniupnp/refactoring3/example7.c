switch(ife->ifa_addr->sa_family)
		{
		case AF_INET:
			/* IPv4-mapped IPv6 address ::ffff:1.2.3.4 */
			memset(addr->s6_addr, 0, 10);
			addr->s6_addr[10] = 0xff;
			addr->s6_addr[11] = 0xff;
			memcpy(addr->s6_addr + 12,
			       &(((struct sockaddr_in *)ife->ifa_addr)->sin_addr.s_addr),
			       4);
			found = 1;
			break;

#ifdef ENABLE_IPV6
		case AF_INET6:
			tmpaddr = (const struct sockaddr_in6 *)ife->ifa_addr;
			if(!IN6_IS_ADDR_LOOPBACK(&tmpaddr->sin6_addr)
			   && !IN6_IS_ADDR_LINKLOCAL(&tmpaddr->sin6_addr))
			{
				memcpy(addr->s6_addr,
				       &tmpaddr->sin6_addr,
				       16);
				found = 1;
			}
			break;
#endif /* ENABLE_IPV6 */
		}
