switch (sa->sa_family) {
    case AF_INET : {
	const struct sockaddr_in *sin4 = (const struct sockaddr_in *)sa;
	return rk_UNCONST(&sin4->sin_addr);
    }
#ifdef HAVE_IPV6
    case AF_INET6 : {
	const struct sockaddr_in6 *sin6 = (const struct sockaddr_in6 *)sa;
	return rk_UNCONST(&sin6->sin6_addr);
    }
#endif
    default:
	return NULL;
    }
