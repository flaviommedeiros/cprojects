switch (family) {
	case AF_INET:
		sock->client_addr_len = sizeof (struct sockaddr_in);
		memset (&sock->client_addr, 0, sock->client_addr_len);
		break;
#ifdef HAVE_IPV6
	case AF_INET6:
		sock->client_addr_len = sizeof (struct sockaddr_in6);
		memset (&sock->client_addr, 0, sock->client_addr_len);
		break;
#endif
#ifdef HAVE_SOCKADDR_UN
	case AF_UNIX:
		memset (&sock->client_addr, 0, sizeof (struct sockaddr_un));
		break;
#endif
	default:
		SHOULDNT_HAPPEN;
		return ret_error;
	}
