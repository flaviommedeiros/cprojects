switch (family) {
	case AF_INET:
		((struct sockaddr_in *)addr)->sin_port = htons(prt);
		break;
#ifdef HAVE_IPV6
	case AF_INET6:
		((struct sockaddr_in6 *)addr)->sin6_port = htons(prt);
		break;
#endif
	}
