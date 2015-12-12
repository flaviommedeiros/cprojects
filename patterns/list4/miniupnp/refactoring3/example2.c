switch(addr->sa_family)
	{
#ifdef AF_INET6
	case AF_INET6:
		if(inet_ntop(addr->sa_family,
		             &((struct sockaddr_in6 *)addr)->sin6_addr,
		             buffer, sizeof(buffer)) == NULL) {
			snprintf(buffer, sizeof(buffer), "inet_ntop: %s", strerror(errno));
		}
		port = ntohs(((struct sockaddr_in6 *)addr)->sin6_port);
		if(((struct sockaddr_in6 *)addr)->sin6_scope_id > 0) {
			char ifname[IF_NAMESIZE];
			if(if_indextoname(((struct sockaddr_in6 *)addr)->sin6_scope_id, ifname) == NULL)
				strncpy(ifname, "ERROR", sizeof(ifname));
			n = snprintf(str, size, "[%s%%%s]:%hu", buffer, ifname, port);
		} else {
			n = snprintf(str, size, "[%s]:%hu", buffer, port);
		}
		break;
#endif /* AF_INET6 */
	case AF_INET:
		if(inet_ntop(addr->sa_family,
		             &((struct sockaddr_in *)addr)->sin_addr,
		             buffer, sizeof(buffer)) == NULL) {
			snprintf(buffer, sizeof(buffer), "inet_ntop: %s", strerror(errno));
		}
		port = ntohs(((struct sockaddr_in *)addr)->sin_port);
		n = snprintf(str, size, "%s:%hu", buffer, port);
		break;
#ifdef AF_LINK
#if defined(__sun)
		/* solaris does not seem to have link_ntoa */
		/* #define link_ntoa _link_ntoa	*/
#define link_ntoa(x) "dummy-link_ntoa"
#endif
	case AF_LINK:
		{
			struct sockaddr_dl * sdl = (struct sockaddr_dl *)addr;
			n = snprintf(str, size, "index=%hu type=%d %s",
			             sdl->sdl_index, sdl->sdl_type,
			             link_ntoa(sdl));
		}
		break;
#endif	/* AF_LINK */
	default:
		n = snprintf(str, size, "unknown address family %d", addr->sa_family);
#if 0
		n = snprintf(str, size, "unknown address family %d "
		             "%02x %02x %02x %02x %02x %02x %02x %02x",
		             addr->sa_family,
		             addr->sa_data[0], addr->sa_data[1], (unsigned)addr->sa_data[2], addr->sa_data[3],
		             addr->sa_data[4], addr->sa_data[5], (unsigned)addr->sa_data[6], addr->sa_data[7]);
#endif
	}
