#ifdef SUPPORT_IP6
if ((ctxt->ftpAddr).ss_family == AF_INET6)
	    ((struct sockaddr_in6 *)&dataAddr)->sin6_port = 0;
	else
#endif
	    ((struct sockaddr_in *)&dataAddr)->sin_port = 0;
