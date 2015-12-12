switch (sa->sa_family) {
#ifdef HAVE_IPV6
    case AF_INET6 : {
	const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sa;

	return doit (AF_INET6, &sin6->sin6_addr, sizeof(sin6->sin6_addr),
		     sin6->sin6_port,
		     host, hostlen,
		     serv, servlen,
		     flags);
    }
#endif
    case AF_INET : {
	const struct sockaddr_in *sin4 = (const struct sockaddr_in *)sa;

	return doit (AF_INET, &sin4->sin_addr, sizeof(sin4->sin_addr),
		     sin4->sin_port,
		     host, hostlen,
		     serv, servlen,
		     flags);
    }
    default :
	return EAI_FAMILY;
    }
