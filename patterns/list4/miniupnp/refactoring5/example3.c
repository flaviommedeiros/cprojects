#ifdef ENABLE_IPV6
if(ipv6)
	{
		struct sockaddr_in6 * saddr = (struct sockaddr_in6 *)&sockname;
		saddr->sin6_family = AF_INET6;
		saddr->sin6_port = htons(SSDP_PORT);
		saddr->sin6_addr = ipv6_bind_addr;
		sockname_len = sizeof(struct sockaddr_in6);
	}
	else
#endif /* ENABLE_IPV6 */
	{
		struct sockaddr_in * saddr = (struct sockaddr_in *)&sockname;
		saddr->sin_family = AF_INET;
		saddr->sin_port = htons(SSDP_PORT);
		/* NOTE : it seems it doesnt work when binding on the specific address */
		/*saddr->sin_addr.s_addr = inet_addr(UPNP_MCAST_ADDR);*/
		saddr->sin_addr.s_addr = htonl(INADDR_ANY);
		/*saddr->sin_addr.s_addr = inet_addr(ifaddr);*/
		sockname_len = sizeof(struct sockaddr_in);
	}
