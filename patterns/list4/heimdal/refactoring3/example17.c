switch (af) {
    case AF_INET :
	return inet_ntop_v4 (src, dst, size);
#ifdef HAVE_IPV6
    case AF_INET6 :
	return inet_ntop_v6 (src, dst, size);
#endif
    default :
	errno = EAFNOSUPPORT;
	return NULL;
    }
