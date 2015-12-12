#ifdef HAVE_UNIX_SOCKETS
if (family == AF_UNIX)
	{
		/*
		 * Create unixSocketPath from portNumber and unixSocketDir and lock
		 * that file path
		 */
		UNIXSOCK_PATH(unixSocketPath, portNumber, unixSocketDir);
		if (strlen(unixSocketPath) >= UNIXSOCK_PATH_BUFLEN)
		{
			ereport(LOG,
					(errmsg("Unix-domain socket path \"%s\" is too long (maximum %d bytes)",
							unixSocketPath,
							(int) (UNIXSOCK_PATH_BUFLEN - 1))));
			return STATUS_ERROR;
		}
		if (Lock_AF_UNIX(unixSocketDir, unixSocketPath) != STATUS_OK)
			return STATUS_ERROR;
		service = unixSocketPath;
	}
	else
#endif   /* HAVE_UNIX_SOCKETS */
	{
		snprintf(portNumberStr, sizeof(portNumberStr), "%d", portNumber);
		service = portNumberStr;
	}
