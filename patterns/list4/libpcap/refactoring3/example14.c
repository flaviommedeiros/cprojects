switch (addr->sa_family) {

#ifdef AF_INET
	case AF_INET:
		return (sizeof (struct sockaddr_in));
#endif

#ifdef AF_INET6
	case AF_INET6:
		return (sizeof (struct sockaddr_in6));
#endif

#if (defined(linux) || defined(__Lynx__)) && defined(AF_PACKET)
	case AF_PACKET:
		return (sizeof (struct sockaddr_ll));
#endif

	default:
		return (sizeof (struct sockaddr));
	}
