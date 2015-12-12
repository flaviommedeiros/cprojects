switch (sa->sa_family) {
    case AF_INET :
	return sizeof(struct in_addr);
#ifdef HAVE_IPV6
    case AF_INET6 :
	return sizeof(struct in6_addr);
#endif
    default :
	return 0;
    }
