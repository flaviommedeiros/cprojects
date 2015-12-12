static void
SendSSDPNotify(int s, const struct sockaddr * dest, socklen_t dest_len,
               const char * dest_str,
               const char * host, unsigned short http_port,
#ifdef ENABLE_HTTPS
               unsigned short https_port,
#endif
               const char * nt, const char * suffix,
               const char * usn1, const char * usn2, const char * usn3,
               unsigned int lifetime)
{
	char bufr[SSDP_PACKET_MAX_LEN];
	int n, l;

	l = snprintf(bufr, sizeof(bufr),
		"NOTIFY * HTTP/1.1\r\n"
		"HOST: %s:%d\r\n"
		"CACHE-CONTROL: max-age=%u\r\n"
		"LOCATION: http://%s:%u" ROOTDESC_PATH "\r\n"
#ifdef ENABLE_HTTPS
		"SECURELOCATION.UPNP.ORG: https://%s:%u" ROOTDESC_PATH "\r\n"
#endif
		"SERVER: " MINIUPNPD_SERVER_STRING "\r\n"
		"NT: %s%s\r\n"
		"USN: %s%s%s%s\r\n"
		"NTS: ssdp:alive\r\n"
		"OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n" /* UDA v1.1 */
		"01-NLS: %u\r\n" /* same as BOOTID field. UDA v1.1 */
		"BOOTID.UPNP.ORG: %u\r\n" /* UDA v1.1 */
		"CONFIGID.UPNP.ORG: %u\r\n" /* UDA v1.1 */
		"\r\n",
		dest_str, SSDP_PORT,			/* HOST: */
		lifetime,						/* CACHE-CONTROL: */
		host, (unsigned int)http_port,	/* LOCATION: */
#ifdef ENABLE_HTTPS
		host, (unsigned int)https_port,	/* SECURE-LOCATION: */
#endif
		nt, suffix,						/* NT: */
		usn1, usn2, usn3, suffix,		/* USN: */
		upnp_bootid,					/* 01-NLS: */
		upnp_bootid,					/* BOOTID.UPNP.ORG: */
		upnp_configid );				/* CONFIGID.UPNP.ORG: */
	if(l<0) {
		syslog(LOG_ERR, "%s: snprintf error", "SendSSDPNotify()");
		return;
	} else if((unsigned int)l >= sizeof(bufr)) {
		syslog(LOG_WARNING, "%s: truncated output (%u>=%u)",
		       "SendSSDPNotify()", (unsigned)l, (unsigned)sizeof(bufr));
		l = sizeof(bufr) - 1;
	}
	n = sendto_or_schedule(s, bufr, l, 0, dest, dest_len);
	if(n < 0) {
		syslog(LOG_ERR, "sendto(udp_notify=%d, %s): %m", s,
		       host ? host : "NULL");
	} else if(n != l) {
		syslog(LOG_NOTICE, "sendto() sent %d out of %d bytes", n, l);
	}
	/* Due to the unreliable nature of UDP, devices SHOULD send the entire
	 * set of discovery messages more than once with some delay between
	 * sets e.g. a few hundred milliseconds. To avoid network congestion
	 * discovery messages SHOULD NOT be sent more than three times. */
	n = sendto_schedule(s, bufr, l, 0, dest, dest_len, 250);
	if(n < 0) {
		syslog(LOG_ERR, "sendto(udp_notify=%d, %s): %m", s,
		       host ? host : "NULL");
	}
}
