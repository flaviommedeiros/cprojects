#ifdef IPTABLES_143
if(!iptc_delete_num_entry(miniupnpd_chain, index, h))
#else
	if(!iptc_delete_num_entry(miniupnpd_chain, index, &h))
#endif
	{
		syslog(LOG_ERR, "%s() : iptc_delete_num_entry(): %s\n",
	    	   logcaller, iptc_strerror(errno));
		r = -1;
	}
#ifdef IPTABLES_143
	else if(!iptc_commit(h))
#else
	else if(!iptc_commit(&h))
#endif
	{
		syslog(LOG_ERR, "%s() : iptc_commit(): %s\n",
	    	   logcaller, iptc_strerror(errno));
		r = -1;
	}
