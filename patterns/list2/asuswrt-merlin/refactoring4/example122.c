#ifndef HAVE_IP_MREQN
if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&imr, sizeof(struct ip_mreq)) < 0)
#else	/* HAVE_IP_MREQN */
	if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&imr, sizeof(struct ip_mreqn)) < 0)
#endif	/* HAVE_IP_MREQN */
	{
        syslog(LOG_ERR, "setsockopt(udp, IP_ADD_MEMBERSHIP): %m");
		return -1;
    }
