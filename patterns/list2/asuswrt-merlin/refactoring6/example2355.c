if ((x->props.family == AF_INET &&
	     x->sel.saddr.a4 != x->props.saddr.a4)
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	    || (x->props.family == AF_INET6 &&
		memcmp (x->sel.saddr.a6, x->props.saddr.a6, sizeof (struct in6_addr)))
#endif
		)
		size += sizeof(struct sadb_address) + sockaddr_size;
