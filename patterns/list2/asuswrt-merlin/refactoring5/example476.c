#ifdef HAVE_GETSERVBYNAME
if ((serv = getservbyname("pptp", "tcp")) != NULL) {
		address.sin_port = serv->s_port;
	} else
#endif
		address.sin_port = htons(PPTP_PORT);
