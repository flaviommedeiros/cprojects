#ifdef SUPPORT_IP6
if ((ctxt->ftpAddr).ss_family == AF_INET6) {
	    char buf6[INET6_ADDRSTRLEN];
	    inet_ntop (AF_INET6, &((struct sockaddr_in6 *)&dataAddr)->sin6_addr,
		    buf6, INET6_ADDRSTRLEN);
	    adp = (unsigned char *) buf6;
	    portp = (unsigned char *) &((struct sockaddr_in6 *)&dataAddr)->sin6_port;
	    snprintf (buf, sizeof(buf), "EPRT |2|%s|%s|\r\n", adp, portp);
        } else
#endif
	{
	    adp = (unsigned char *) &((struct sockaddr_in *)&dataAddr)->sin_addr;
	    portp = (unsigned char *) &((struct sockaddr_in *)&dataAddr)->sin_port;
	    snprintf (buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",
	    adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,
	    portp[0] & 0xff, portp[1] & 0xff);
	}
