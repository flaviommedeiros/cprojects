if (s_addr->sa_family != AF_INET
#if IS_ENABLED(CONFIG_IPV6)
	    && s_addr->sa_family != AF_INET6
#endif
		)
		return 0;
