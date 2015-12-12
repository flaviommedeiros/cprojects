switch (si->family) {
	case AF_INET: {
		const struct sockaddr_in *in =
		    (const struct sockaddr_in *)inaddr;
		unsigned int addr = ntohl(in->sin_addr.s_addr);
		char u_type = '\0';
		char d_type = '\0';
		char b_type = '\0';
		char a_type = '\0';

		prt = ntohs(in->sin_port);

		switch (si->type) {
		case SOCK_STREAM:
			u_type = SOCKET_TYPE_CHAR_TCP;
			d_type = SOCKET_TYPE_CHAR_TCP;
			break;
		case SOCK_DGRAM:
			u_type = SOCKET_TYPE_CHAR_UDP;
			d_type = SOCKET_TYPE_CHAR_UDP;
			a_type = SOCKET_TYPE_CHAR_UDP;
			b_type = SOCKET_TYPE_CHAR_UDP;
			break;
		}

		if (addr == 0) {
			/* 0.0.0.0 */
		 	is_bcast = 0;
			type = d_type;
			iface = socket_wrapper_default_iface();
		} else if (a_type && addr == 0xFFFFFFFF) {
			/* 255.255.255.255 only udp */
			is_bcast = 2;
			type = a_type;
			iface = socket_wrapper_default_iface();
		} else if (b_type && addr == 0x7FFFFFFF) {
			/* 127.255.255.255 only udp */
			is_bcast = 1;
			type = b_type;
			iface = socket_wrapper_default_iface();
		} else if ((addr & 0xFFFFFF00) == 0x7F000000) {
			/* 127.0.0.X */
			is_bcast = 0;
			type = u_type;
			iface = (addr & 0x000000FF);
		} else {
			errno = EADDRNOTAVAIL;
			return -1;
		}
		break;
	}
#ifdef HAVE_IPV6
	case AF_INET6: {
		const struct sockaddr_in6 *in =
		    (const struct sockaddr_in6 *)inaddr;

		switch (si->type) {
		case SOCK_STREAM:
			type = SOCKET_TYPE_CHAR_TCP_V6;
			break;
		case SOCK_DGRAM:
			type = SOCKET_TYPE_CHAR_UDP_V6;
			break;
		}

		/* XXX no multicast/broadcast */

		prt = ntohs(in->sin6_port);
		iface = SW_IPV6_ADDRESS;

		break;
	}
#endif
	default:
		errno = ENETUNREACH;
		return -1;
	}
