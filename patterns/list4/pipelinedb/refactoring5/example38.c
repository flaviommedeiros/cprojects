#ifdef HAVE_UNIX_SOCKETS
if (IS_AF_UNIX(conn->raddr.addr.ss_family))
	{
		char		service[NI_MAXHOST];

		pg_getnameinfo_all(&conn->raddr.addr, conn->raddr.salen,
						   NULL, 0,
						   service, sizeof(service),
						   NI_NUMERICSERV);
		appendPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("could not connect to server: %s\n"
							"\tIs the server running locally and accepting\n"
							"\tconnections on Unix domain socket \"%s\"?\n"),
						  SOCK_STRERROR(errorno, sebuf, sizeof(sebuf)),
						  service);
	}
	else
#endif   /* HAVE_UNIX_SOCKETS */
	{
		char		host_addr[NI_MAXHOST];
		const char *displayed_host;
		struct sockaddr_storage *addr = &conn->raddr.addr;

		/*
		 * Optionally display the network address with the hostname. This is
		 * useful to distinguish between IPv4 and IPv6 connections.
		 */
		if (conn->pghostaddr != NULL)
			strlcpy(host_addr, conn->pghostaddr, NI_MAXHOST);
		else if (addr->ss_family == AF_INET)
		{
			if (inet_net_ntop(AF_INET,
							  &((struct sockaddr_in *) addr)->sin_addr.s_addr,
							  32,
							  host_addr, sizeof(host_addr)) == NULL)
				strcpy(host_addr, "???");
		}
#ifdef HAVE_IPV6
		else if (addr->ss_family == AF_INET6)
		{
			if (inet_net_ntop(AF_INET6,
						  &((struct sockaddr_in6 *) addr)->sin6_addr.s6_addr,
							  128,
							  host_addr, sizeof(host_addr)) == NULL)
				strcpy(host_addr, "???");
		}
#endif
		else
			strcpy(host_addr, "???");

		if (conn->pghostaddr && conn->pghostaddr[0] != '\0')
			displayed_host = conn->pghostaddr;
		else if (conn->pghost && conn->pghost[0] != '\0')
			displayed_host = conn->pghost;
		else
			displayed_host = DefaultHost;

		/*
		 * If the user did not supply an IP address using 'hostaddr', and
		 * 'host' was missing or does not match our lookup, display the
		 * looked-up IP address.
		 */
		if ((conn->pghostaddr == NULL) &&
			(conn->pghost == NULL || strcmp(conn->pghost, host_addr) != 0))
			appendPQExpBuffer(&conn->errorMessage,
							libpq_gettext("could not connect to server: %s\n"
				"\tIs the server running on host \"%s\" (%s) and accepting\n"
									   "\tTCP/IP connections on port %s?\n"),
							  SOCK_STRERROR(errorno, sebuf, sizeof(sebuf)),
							  displayed_host,
							  host_addr,
							  conn->pgport);
		else
			appendPQExpBuffer(&conn->errorMessage,
							libpq_gettext("could not connect to server: %s\n"
					 "\tIs the server running on host \"%s\" and accepting\n"
									   "\tTCP/IP connections on port %s?\n"),
							  SOCK_STRERROR(errorno, sebuf, sizeof(sebuf)),
							  displayed_host,
							  conn->pgport);
	}
