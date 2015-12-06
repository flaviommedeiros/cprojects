if (addr->sa.sa_family == AF_INET)
	{
		const struct sockaddr_in *v4 = (const struct sockaddr_in *)addr;
		cp = (const unsigned char *)&v4->sin_addr.s_addr;

		sprintf(request->queryname, "%u.%u.%u.%u.in-addr.arpa", (unsigned int)(cp[3]),
			(unsigned int)(cp[2]), (unsigned int)(cp[1]), (unsigned int)(cp[0]));
	}
#ifdef RB_IPV6
	else if (addr->sa.sa_family == AF_INET6)
	{
		const struct sockaddr_in6 *v6 = (const struct sockaddr_in6 *)addr;
		cp = (const unsigned char *)&v6->sin6_addr.s6_addr;

		(void)sprintf(request->queryname, "%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x."
			      "%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.ip6.arpa",
			      (unsigned int)(cp[15] & 0xf), (unsigned int)(cp[15] >> 4),
			      (unsigned int)(cp[14] & 0xf), (unsigned int)(cp[14] >> 4),
			      (unsigned int)(cp[13] & 0xf), (unsigned int)(cp[13] >> 4),
			      (unsigned int)(cp[12] & 0xf), (unsigned int)(cp[12] >> 4),
			      (unsigned int)(cp[11] & 0xf), (unsigned int)(cp[11] >> 4),
			      (unsigned int)(cp[10] & 0xf), (unsigned int)(cp[10] >> 4),
			      (unsigned int)(cp[9] & 0xf), (unsigned int)(cp[9] >> 4),
			      (unsigned int)(cp[8] & 0xf), (unsigned int)(cp[8] >> 4),
			      (unsigned int)(cp[7] & 0xf), (unsigned int)(cp[7] >> 4),
			      (unsigned int)(cp[6] & 0xf), (unsigned int)(cp[6] >> 4),
			      (unsigned int)(cp[5] & 0xf), (unsigned int)(cp[5] >> 4),
			      (unsigned int)(cp[4] & 0xf), (unsigned int)(cp[4] >> 4),
			      (unsigned int)(cp[3] & 0xf), (unsigned int)(cp[3] >> 4),
			      (unsigned int)(cp[2] & 0xf), (unsigned int)(cp[2] >> 4),
			      (unsigned int)(cp[1] & 0xf), (unsigned int)(cp[1] >> 4),
			      (unsigned int)(cp[0] & 0xf), (unsigned int)(cp[0] >> 4));
	}
#endif
