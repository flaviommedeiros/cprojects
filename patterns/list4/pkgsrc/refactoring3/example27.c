switch (af) {
	case AF_INET:
		return (inet_ntop4(src, dst, size));
#ifdef INET6
	case AF_INET6:
		return (inet_ntop6(src, dst, size));
#endif /* INET6 */
	default:
		errno = EAFNOSUPPORT;
		return (NULL);
	}
