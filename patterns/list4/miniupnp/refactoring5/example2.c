#ifdef SSDP_LISTEN_ON_SPECIFIC_ADDR
if(n_listen_addr == 1)
	{
		sockname.sin_addr.s_addr = GetIfAddrIPv4(listen_addr[0]);
		if(sockname.sin_addr.s_addr == INADDR_NONE)
		{
			syslog(LOG_ERR, "no IPv4 address for interface %s",
			       listen_addr[0]);
			close(s);
			return -1;
		}
	}
	else
#endif /* SSDP_LISTEN_ON_SPECIFIC_ADDR */
	sockname.sin_addr.s_addr = htonl(INADDR_ANY);
