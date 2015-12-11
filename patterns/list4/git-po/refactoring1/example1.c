if (addr->sa_family == AF_INET) {
		char buf[128] = "";
		struct sockaddr_in *sin_addr = (void *) addr;
		inet_ntop(addr->sa_family, &sin_addr->sin_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=%s", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin_addr->sin_port));
#ifndef NO_IPV6
	} else if (addr->sa_family == AF_INET6) {
		char buf[128] = "";
		struct sockaddr_in6 *sin6_addr = (void *) addr;
		inet_ntop(AF_INET6, &sin6_addr->sin6_addr, buf, sizeof(buf));
		argv_array_pushf(&cld.env_array, "REMOTE_ADDR=[%s]", buf);
		argv_array_pushf(&cld.env_array, "REMOTE_PORT=%d",
				 ntohs(sin6_addr->sin6_port));
#endif
	}
#endif
