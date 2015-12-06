#ifdef SUPPORT_IP6
if ((ctxt->ftpAddr).ss_family == AF_INET6) {
	ctxt->dataFd = socket (AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	((struct sockaddr_in6 *)&dataAddr)->sin6_family = AF_INET6;
	dataAddrLen = sizeof(struct sockaddr_in6);
    } else
#endif
    {
	ctxt->dataFd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	((struct sockaddr_in *)&dataAddr)->sin_family = AF_INET;
	dataAddrLen = sizeof (struct sockaddr_in);
    }
