#ifdef HAVE_UNIX_SOCKETS
if (hint_ai_family == AF_UNIX)
	{
		/* struct was built by getaddrinfo_unix (see pg_getaddrinfo_all) */
		while (ai != NULL)
		{
			struct addrinfo *p = ai;

			ai = ai->ai_next;
			free(p->ai_addr);
			free(p);
		}
	}
	else
#endif   /* HAVE_UNIX_SOCKETS */
	{
		/* struct was built by getaddrinfo() */
		if (ai != NULL)
			freeaddrinfo(ai);
	}
