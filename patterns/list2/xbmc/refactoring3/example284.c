switch (sa->sa_family) {
	case AF_INET:
		v4a = ((struct sockaddr_in *)sa)->sin_addr.s_addr;
		if (IN_MULTICAST(v4a) || IN_EXPERIMENTAL(v4a))
			flags |= NI_NUMERICHOST;
		v4a >>= IN_CLASSA_NSHIFT;
		if (v4a == 0 || v4a == IN_LOOPBACKNET)
			flags |= NI_NUMERICHOST;			
		break;
#ifdef ENABLE_IPV6
	case AF_INET6:
		pfx = ((struct sockaddr_in6 *)sa)->sin6_addr.s6_addr8[0];
		if (pfx == 0 || pfx == 0xfe || pfx == 0xff)
			flags |= NI_NUMERICHOST;
		break;
#endif
	}
