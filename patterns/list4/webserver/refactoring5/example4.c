#ifdef HAVE_IPV6
if (SOCKET_AF(socket) == AF_INET6) {
		ip     = (char *)&SOCKET_ADDRESS_IPv6(socket);
		ip_len = 16;
	} else
#endif
	{
		ip     = (char *)&SOCKET_ADDRESS_IPv4(socket);
		ip_len = 4;
	}
