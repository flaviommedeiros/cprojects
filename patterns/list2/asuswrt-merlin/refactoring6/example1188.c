if( sinaddr.sa_family == 0
#if defined(AF_LOCAL)
	 	|| sinaddr.sa_family == AF_LOCAL
#endif
#if defined(AF_UNIX)
	 	|| sinaddr.sa_family == AF_UNIX
#endif
		){
		/* force the localhost address */
		int len;
		void *s, *addr;
		memset( &sinaddr, 0, sizeof(sinaddr) );
		Perm_check.unix_socket = 1;
	 	sinaddr.sa_family = Localhost_IP.h_addrtype;
		len = Localhost_IP.h_length;
		if( sinaddr.sa_family == AF_INET ){
			addr = &(((struct sockaddr_in *)&sinaddr)->sin_addr);
#if defined(IPV6)
		} else if( sinaddr->sa_family == AF_INET6 ){
			addr = &(((struct sockaddr_in6 *)&sinaddr)->sin6_addr);
#endif
		} else {
			FATAL(LOG_INFO) _("Service_connection: BAD LocalHost_IP value"));
			addr = 0;
		}
