switch (family) {
	case AF_INET:
#ifdef HAVE_IPV6
	case AF_INET6:
#endif
		break;
	case AF_UNIX:
		return real_socket(family, type, protocol);
	default:
		errno = EAFNOSUPPORT;
		return -1;
	}
