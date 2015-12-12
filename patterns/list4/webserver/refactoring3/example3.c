switch (SOCKET_AF(socket)) {
	case AF_INET:
#ifdef HAVE_INET_PTON
		re = inet_pton (AF_INET, host->buf, &SOCKET_SIN_ADDR(socket));
		if (re <= 0) return ret_error;
#else
		re = inet_aton (host->buf, &SOCKET_SIN_ADDR(socket));
		if (re == 0) return ret_error;
#endif
		break;
#ifdef HAVE_IPV6
	case AF_INET6:
		re = inet_pton (AF_INET6, host->buf, &SOCKET_SIN6_ADDR(socket));
		if (re <= 0) return ret_error;
		break;
#endif
	default:
		LOG_CRITICAL (CHEROKEE_ERROR_SOCKET_BAD_FAMILY, SOCKET_AF(socket));
		return ret_error;
	}
