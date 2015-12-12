#ifdef ENABLE_IPV6
if( (s = socket(ipv6 ? PF_INET6 : PF_INET, SOCK_DGRAM, 0)) < 0)
#else /* ENABLE_IPV6 */
	if( (s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
#endif /* ENABLE_IPV6 */
	{
		syslog(LOG_ERR, "socket(udp): %m");
		return -1;
	}
