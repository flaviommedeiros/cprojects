#ifdef IPTABLES_143
if(!iptc_commit(h))
#else
	else if(!iptc_commit(&h))
#endif
	{
		syslog(LOG_ERR, "%s() : iptc_commit(): %s\n",
	    	   logcaller, iptc_strerror(errno));
		r = -1;
	}
