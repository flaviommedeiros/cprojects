if (addr->sa_family == AF_INET) {
		result = rep_inet_ntop(AF_INET,
				       &((struct sockaddr_in *)addr)->sin_addr,
				       addrstring,
				       addrlen);
#ifdef HAVE_STRUCT_SOCKADDR_IN6
	} else if (addr->sa_family == AF_INET6) {
		result = rep_inet_ntop(AF_INET6,
				       &((struct sockaddr_in6 *)addr)->sin6_addr,
				       addrstring,
				       addrlen);
#endif
	}
#endif
