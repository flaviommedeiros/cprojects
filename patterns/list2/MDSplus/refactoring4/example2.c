#if defined(HAVE_GETADDRINFO) && !defined(GLOBUS)
if (((getaddr_status == 0) ? memcmp(&sockaddr, &hostchk->sockaddr,
					sizeof(sockaddr)) : strcmp(hostchk->host, host)) == 0)
#else
    if (strcmp(hostchk->host, host) == 0)
#endif
    {
      hostchk->time = time(0);
      if (inc_count)
	hostchk->connections++;
      socket = hostchk->socket;
    }
