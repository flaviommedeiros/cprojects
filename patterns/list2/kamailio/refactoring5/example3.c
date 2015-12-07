#ifdef DNS_SRV_LB
if (tried){
		rr=dns_srv_get_nxt_rr(*e, tried, rr_no, now);
	}else
#endif
	{
		rr=dns_entry_get_rr(*e, rr_no, now);
		(*rr_no)++; /* try next record next time */
	}
