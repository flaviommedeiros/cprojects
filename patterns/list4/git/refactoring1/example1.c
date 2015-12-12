if (addr->sa_family == AF_INET) {
		struct sockaddr_in *sin_addr = (void *) addr;
		inet_ntop(addr->sa_family, &sin_addr->sin_addr, addrbuf + 12,
		    sizeof(addrbuf) - 12);
		snprintf(portbuf, sizeof(portbuf), "REMOTE_PORT=%d",
		    ntohs(sin_addr->sin_port));
#ifndef NO_IPV6
	} else if (addr->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6_addr = (void *) addr;

		char *buf = addrbuf + 12;
		*buf++ = '['; *buf = '\0'; /* stpcpy() is cool */
		inet_ntop(AF_INET6, &sin6_addr->sin6_addr, buf,
		    sizeof(addrbuf) - 13);
		strcat(buf, "]");

		snprintf(portbuf, sizeof(portbuf), "REMOTE_PORT=%d",
		    ntohs(sin6_addr->sin6_port));
#endif
	}
#endif
