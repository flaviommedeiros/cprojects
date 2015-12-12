# ifdef HAVE_IPV6
if (family == AF_INET6) {
		struct in6_addr *addr6 = &(((struct sockaddr_in6 *)addr)->sin6_addr);

		if (IN6_IS_ADDR_V4MAPPED (addr6) ||
		    IN6_IS_ADDR_V4COMPAT (addr6))
		{
			const void *p = &(addr6)->s6_addr[12];

			str = inet_ntop (AF_INET, p, dst, cnt);
			if (str == NULL) {
				goto error;
			}
		} else {
			str = (char *) inet_ntop (AF_INET6, addr6, dst, cnt);
			if (str == NULL) {
				goto error;
			}
		}
	} else
# endif
	{
		struct in_addr *addr4 = &((struct sockaddr_in *)addr)->sin_addr;

		str = inet_ntop (AF_INET, addr4, dst, cnt);
		if (str == NULL) {
			goto error;
		}
	}
