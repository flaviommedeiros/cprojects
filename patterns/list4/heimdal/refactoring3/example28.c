switch (si->family) {
	case AF_INET: {
		struct sockaddr_in in;

		switch (si->type) {
		case SOCK_STREAM:
			type = SOCKET_TYPE_CHAR_TCP;
			break;
		case SOCK_DGRAM:
		    	type = SOCKET_TYPE_CHAR_UDP;
			break;
		default:
		    errno = ESOCKTNOSUPPORT;
		    return -1;
		}

		memset(&in, 0, sizeof(in));
		in.sin_family = AF_INET;
		in.sin_addr.s_addr = htonl(127<<24 |
					   socket_wrapper_default_iface());

		si->myname_len = sizeof(in);
		si->myname = sockaddr_dup(&in, si->myname_len);
		break;
	}
#ifdef HAVE_IPV6
	case AF_INET6: {
		struct sockaddr_in6 in6;

		switch (si->type) {
		case SOCK_STREAM:
			type = SOCKET_TYPE_CHAR_TCP_V6;
			break;
		case SOCK_DGRAM:
		    	type = SOCKET_TYPE_CHAR_UDP_V6;
			break;
		default:
		    errno = ESOCKTNOSUPPORT;
		    return -1;
		}

		memset(&in6, 0, sizeof(in6));
		in6.sin6_family = AF_INET6;
		in6.sin6_addr.s6_addr[0] = SW_IPV6_ADDRESS;
		si->myname_len = sizeof(in6);
		si->myname = sockaddr_dup(&in6, si->myname_len);
		break;
	}
#endif
	default:
		errno = ESOCKTNOSUPPORT;
		return -1;
	}
