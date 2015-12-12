static void
SendSSDPResponse(int s, const struct sockaddr * addr,
                 const char * st, int st_len, const char * suffix,
                 const char * host, unsigned short http_port,
#ifdef ENABLE_HTTPS
                 unsigned short https_port,
#endif
                 const char * uuidvalue, unsigned int delay)
{
	int l, n;
	char buf[SSDP_PACKET_MAX_LEN];
	char addr_str[64];
	socklen_t addrlen;
	int st_is_uuid;
#ifdef ENABLE_HTTP_DATE
	char http_date[64];
	time_t t;
	struct tm tm;

	time(&t);
	gmtime_r(&t, &tm);
	strftime(http_date, sizeof(http_date),
		    "%a, %d %b %Y %H:%M:%S GMT", &tm);
#endif

	st_is_uuid = (st_len == (int)strlen(uuidvalue)) &&
	              (memcmp(uuidvalue, st, st_len) == 0);
	/*
	 * follow guideline from document "UPnP Device Architecture 1.0"
	 * uppercase is recommended.
	 * DATE: is recommended
	 * SERVER: OS/ver UPnP/1.0 miniupnpd/1.0
	 * - check what to put in the 'Cache-Control' header
	 *
	 * have a look at the document "UPnP Device Architecture v1.1 */
	l = snprintf(buf, sizeof(buf), "HTTP/1.1 200 OK\r\n"
		"CACHE-CONTROL: max-age=120\r\n"
#ifdef ENABLE_HTTP_DATE
		"DATE: %s\r\n"
#endif
		"ST: %.*s%s\r\n"
		"USN: %s%s%.*s%s\r\n"
		"EXT:\r\n"
		"SERVER: " MINIUPNPD_SERVER_STRING "\r\n"
		"LOCATION: http://%s:%u" ROOTDESC_PATH "\r\n"
#ifdef ENABLE_HTTPS
		"SECURELOCATION.UPNP.ORG: https://%s:%u" ROOTDESC_PATH "\r\n"
#endif
		"OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n" /* UDA v1.1 */
		"01-NLS: %u\r\n" /* same as BOOTID. UDA v1.1 */
		"BOOTID.UPNP.ORG: %u\r\n" /* UDA v1.1 */
		"CONFIGID.UPNP.ORG: %u\r\n" /* UDA v1.1 */
		"\r\n",
#ifdef ENABLE_HTTP_DATE
		http_date,
#endif
		st_len, st, suffix,
		uuidvalue, st_is_uuid ? "" : "::",
		st_is_uuid ? 0 : st_len, st, suffix,
		host, (unsigned int)http_port,
#ifdef ENABLE_HTTPS
		host, (unsigned int)https_port,
#endif
		upnp_bootid, upnp_bootid, upnp_configid);
	if(l<0)
	{
		syslog(LOG_ERR, "%s: snprintf failed %m",
		       "SendSSDPResponse()");
		return;
	}
	else if((unsigned)l>=sizeof(buf))
	{
		syslog(LOG_WARNING, "%s: truncated output (%u>=%u)",
		       "SendSSDPResponse()", (unsigned)l, (unsigned)sizeof(buf));
		l = sizeof(buf) - 1;
	}
	addrlen = (addr->sa_family == AF_INET6)
	          ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in);
	n = sendto_schedule(s, buf, l, 0,
	                    addr, addrlen, delay);
	sockaddr_to_string(addr, addr_str, sizeof(addr_str));
	syslog(LOG_DEBUG, "%s: %d bytes to %s ST: %.*s",
	       "SendSSDPResponse()",
	       n, addr_str, l, buf);
	if(n < 0)
	{
		syslog(LOG_ERR, "%s: sendto(udp): %m",
		       "SendSSDPResponse()");
	}
}
