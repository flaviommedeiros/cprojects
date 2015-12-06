if (!com_dedicated || com_dedicated->integer != 2 || !(netenabled & (
#ifdef FEATURE_IPV6
	                                                           NET_ENABLEV6 |
#endif
	                                                           NET_ENABLEV4)))
	{
		return;     // only dedicated servers send heartbeats

	}
