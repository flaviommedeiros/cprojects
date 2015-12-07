#if ENABLE_FEATURE_IPV6
if (!sa)
#endif
		sa = (struct sockaddr*)&_res.nsaddr_list[0];
