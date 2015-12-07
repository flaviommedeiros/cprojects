#if IPFILTER_VERSION >= 5000000
if( (eport == ntohs(ipn.in_dpmax))
		  && (ipn.in_pr[0] == proto)
		  && (startport <= eport) && (eport <= endport) )
#else
		eport = ntohs(ipn.in_pmin);
