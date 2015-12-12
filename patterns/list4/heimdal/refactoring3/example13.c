switch (sa->sa_family) {
    case AF_INET :
	return sizeof(struct sockaddr_in);
#ifdef HAVE_IPV6
    case AF_INET6 :
	return sizeof(struct sockaddr_in6);
#endif
    default:
	return 0;
    }
