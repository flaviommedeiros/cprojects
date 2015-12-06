#ifdef SUPPORT_IP6
if ((ctxt->ftpAddr).ss_family == AF_INET6)
	    snprintf (buf, sizeof(buf), "EPSV\r\n");
	else
#endif
	    snprintf (buf, sizeof(buf), "PASV\r\n");
