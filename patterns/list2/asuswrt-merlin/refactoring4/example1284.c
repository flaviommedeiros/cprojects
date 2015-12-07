#ifndef DEBUG
if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof (opt)) < 0)
#else
	if (setsockopt(sudp, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) < 0)
#endif
	{
		if(error)
			*error = UPNPDISCOVER_SOCKET_ERROR;
		PRINT_SOCKET_ERROR("setsockopt");
		return NULL;
	}
