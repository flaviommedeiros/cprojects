switch (ai->ai_family) {
	case AF_INET:
		socksize = sizeof(struct sockaddr_in);
		memcpy(&sa.sin, ai->ai_addr, socksize);
		sa.sin.sin_port = htons(port);
#ifdef HAVE_SOCK_SIN_LEN
		sa.sin.sin_len = socksize;
#endif
		break;
#ifdef HAVE_SOCKADDR_IN6
	case AF_INET6:
		socksize = sizeof(struct sockaddr_in6);
		memcpy(&sa.sin6, ai->ai_addr, socksize);
		sa.sin6.sin6_port = htons(port);
#ifdef HAVE_SOCK_SIN_LEN
		sa.sin6.sin6_len = socksize;
#endif
		break;
#endif
	default:
		iscsi_set_error(iscsi, "Unknown address family :%d. "
				"Only IPv4/IPv6 supported so far.",
				ai->ai_family);
		freeaddrinfo(ai);
		return -1;

	}
