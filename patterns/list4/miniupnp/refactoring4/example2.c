#ifdef _WIN32
if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_TTL, (const char *)&_ttl, sizeof(_ttl)) < 0)
#else  /* _WIN32 */
	if(setsockopt(sudp, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0)
#endif /* _WIN32 */
	{
		/* not a fatal error */
		PRINT_SOCKET_ERROR("setsockopt(IP_MULTICAST_TTL,...)");
	}
