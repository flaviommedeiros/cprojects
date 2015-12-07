#ifdef ENABLE_IPV6
if(bind(s,
	        ipv6 ? (struct sockaddr *)&listenname6 : (struct sockaddr *)&listenname4,
	        listenname_len) < 0)
#else
	if(bind(s, (struct sockaddr *)&listenname, listenname_len) < 0)
#endif
	{
		syslog(LOG_ERR, "bind(http): %m");
		close(s);
		return -1;
	}
