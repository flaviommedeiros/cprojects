static int
MakeSSDPPacket(const char * dest_str,
               const char * host, unsigned short http_port,
#ifdef ENABLE_HTTPS
               unsigned short https_port,
#endif
               const char * nt, const char * suffix,
               const char * usn1, const char * usn2, const char * usn3,
               unsigned int lifetime)
{
	char bufr[SSDP_PACKET_MAX_LEN];
	int l;

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
		syslog(LOG_ERR, "%s: snprintf error", "MakeSSDPPacket()");
		return -1;
	} else if((unsigned int)l >= sizeof(bufr)) {
		syslog(LOG_WARNING, "%s: truncated output (%u>=%u)",
		       "MakeSSDPPacket()", (unsigned)l, (unsigned)sizeof(bufr));
		l = sizeof(bufr) - 1;
		return -1;
	}
	return 0;
}
