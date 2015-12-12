switch (sa->sa_family) {
    case AF_INET : {
	const struct sockaddr_in *sin4 = (const struct sockaddr_in *)sa;
	return sin4->sin_port;
    }
#ifdef HAVE_IPV6
    case AF_INET6 : {
	const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sa;
	return sin6->sin6_port;
    }
#endif
    default :
	return 0;
    }
