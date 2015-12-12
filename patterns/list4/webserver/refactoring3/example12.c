switch (SOCKET_AF(sock)) {
		case AF_INET:
			r = connect (SOCKET_FD(sock),
			             (struct sockaddr *) &SOCKET_ADDR(sock),
			             sizeof(struct sockaddr_in));
			break;
#ifdef HAVE_IPV6
		case AF_INET6:
			r = connect (SOCKET_FD(sock),
			             (struct sockaddr *) &SOCKET_ADDR(sock),
			             sizeof(struct sockaddr_in6));
			break;
#endif
#ifdef HAVE_SOCKADDR_UN
		case AF_UNIX:
			if (SOCKET_SUN_PATH (socket)[0] != 0) {
				r = connect (SOCKET_FD(sock),
				             (struct sockaddr *) &SOCKET_ADDR(sock),
				             SUN_LEN (SOCKET_ADDR_UNIX(sock)));
			}
			else {
				r = connect (SOCKET_FD(sock),
				             (struct sockaddr *) &SOCKET_ADDR(sock),
				             SUN_ABSTRACT_LEN (SOCKET_ADDR_UNIX(sock)));
			}
			break;
#endif
		default:
			SHOULDNT_HAPPEN;
			return ret_no_sys;
		}
