#ifdef SUPPORT_IP6
if (have_ipv6 ()) {
	struct addrinfo hints, *tmp, *result;

	result = NULL;
	memset (&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;

	if (proxy) {
	    if (getaddrinfo (proxy, NULL, &hints, &result) != 0) {
		__xmlIOErr(XML_FROM_FTP, 0, "getaddrinfo failed");
		return (-1);
	    }
	}
	else
	    if (getaddrinfo (ctxt->hostname, NULL, &hints, &result) != 0) {
		__xmlIOErr(XML_FROM_FTP, 0, "getaddrinfo failed");
		return (-1);
	    }

	for (tmp = result; tmp; tmp = tmp->ai_next)
	    if (tmp->ai_family == AF_INET || tmp->ai_family == AF_INET6)
		break;

	if (!tmp) {
	    if (result)
		freeaddrinfo (result);
	    __xmlIOErr(XML_FROM_FTP, 0, "getaddrinfo failed");
	    return (-1);
	}
	if (tmp->ai_addrlen > sizeof(ctxt->ftpAddr)) {
	    __xmlIOErr(XML_FROM_FTP, 0, "gethostbyname address mismatch");
	    return (-1);
	}
	if (tmp->ai_family == AF_INET6) {
	    memcpy (&ctxt->ftpAddr, tmp->ai_addr, tmp->ai_addrlen);
	    ((struct sockaddr_in6 *) &ctxt->ftpAddr)->sin6_port = htons (port);
	    ctxt->controlFd = socket (AF_INET6, SOCK_STREAM, 0);
	}
	else {
	    memcpy (&ctxt->ftpAddr, tmp->ai_addr, tmp->ai_addrlen);
	    ((struct sockaddr_in *) &ctxt->ftpAddr)->sin_port = htons (port);
	    ctxt->controlFd = socket (AF_INET, SOCK_STREAM, 0);
	}
	addrlen = tmp->ai_addrlen;
	freeaddrinfo (result);
    }
    else
#endif
    {
	if (proxy)
	    hp = gethostbyname (proxy);
	else
	    hp = gethostbyname (ctxt->hostname);
	if (hp == NULL) {
	    __xmlIOErr(XML_FROM_FTP, 0, "gethostbyname failed");
	    return (-1);
	}
	if ((unsigned int) hp->h_length >
	    sizeof(((struct sockaddr_in *)&ctxt->ftpAddr)->sin_addr)) {
	    __xmlIOErr(XML_FROM_FTP, 0, "gethostbyname address mismatch");
	    return (-1);
	}

	/*
	 * Prepare the socket
	 */
	((struct sockaddr_in *)&ctxt->ftpAddr)->sin_family = AF_INET;
	memcpy (&((struct sockaddr_in *)&ctxt->ftpAddr)->sin_addr,
		hp->h_addr_list[0], hp->h_length);
	((struct sockaddr_in *)&ctxt->ftpAddr)->sin_port = htons (port);
	ctxt->controlFd = socket (AF_INET, SOCK_STREAM, 0);
	addrlen = sizeof (struct sockaddr_in);
    }
