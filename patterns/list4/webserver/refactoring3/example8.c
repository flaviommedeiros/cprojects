switch (SOCKET_AF(sock)) {
	case AF_INET:
		return cherokee_bind_v4 (sock, port, listen_to);
#ifdef HAVE_IPV6
	case AF_INET6:
		return cherokee_bind_v6 (sock, port, listen_to);
#endif
#ifdef HAVE_SOCKADDR_UN
	case AF_UNIX:
		return cherokee_bind_local (sock, listen_to);
#endif
	default:
		break;
	}
