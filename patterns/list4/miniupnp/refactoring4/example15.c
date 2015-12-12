#ifdef IPTABLES_143
if(!iptc_append_entry(miniupnpd_chain, e, h))
#else
	if(!iptc_append_entry(miniupnpd_chain, e, &h))
#endif
	{
		syslog(LOG_ERR, "%s : iptc_append_entry() error : %s\n",
		       logcaller, iptc_strerror(errno));
		if(h)
#ifdef IPTABLES_143
			iptc_free(h);
#else
			iptc_free(&h);
#endif
		return -1;
	}
