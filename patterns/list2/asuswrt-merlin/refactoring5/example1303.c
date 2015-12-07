#ifdef SUPPORT_IP6
if ((ctxt->ftpAddr).ss_family == AF_INET6) {
	    if (sscanf (cur, "%u", &temp[0]) != 1) {
		__xmlIOErr(XML_FROM_FTP, XML_FTP_EPSV_ANSWER,
			"Invalid answer to EPSV\n");
		if (ctxt->dataFd != -1) {
		    closesocket (ctxt->dataFd); ctxt->dataFd = -1;
		}
		return (-1);
	    }
	    memcpy (&((struct sockaddr_in6 *)&dataAddr)->sin6_addr, &((struct sockaddr_in6 *)&ctxt->ftpAddr)->sin6_addr, sizeof(struct in6_addr));
	    ((struct sockaddr_in6 *)&dataAddr)->sin6_port = htons (temp[0]);
	}
	else
#endif
	{
	    if (sscanf (cur, "%u,%u,%u,%u,%u,%u", &temp[0], &temp[1], &temp[2],
		&temp[3], &temp[4], &temp[5]) != 6) {
		__xmlIOErr(XML_FROM_FTP, XML_FTP_PASV_ANSWER,
			"Invalid answer to PASV\n");
		if (ctxt->dataFd != -1) {
		    closesocket (ctxt->dataFd); ctxt->dataFd = -1;
		}
		return (-1);
	    }
	    for (i=0; i<6; i++) ad[i] = (unsigned char) (temp[i] & 0xff);
	    memcpy (&((struct sockaddr_in *)&dataAddr)->sin_addr, &ad[0], 4);
	    memcpy (&((struct sockaddr_in *)&dataAddr)->sin_port, &ad[4], 2);
	}
