#ifdef IPTABLES_143
if(!iptc_commit(h))
#else
	if(!iptc_commit(&h))
#endif
	{
		syslog(LOG_ERR, "%s : iptc_commit() error : %s\n",
		       logcaller, iptc_strerror(errno));
		if(h)
#ifdef IPTABLES_143
			iptc_free(h);
#else
			iptc_free(&h);
#endif
		return -1;
	}
